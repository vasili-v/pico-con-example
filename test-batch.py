#!env python3

import sys

import serial

BAUDRATE = 115200

ENQ = b'\x05'
ACK = b'\x06'
NAK = b'\x15'
EOL = b'\n'

class TestException(Exception):
    pass

def empty_command(s):
    s.write(EOL)
    data = s.read_until(ENQ)
    if not data:
        raise TestException(f'Got timeout while expecting prompt (ASCII ENQ) after empty command')

    prompt = data.find(ENQ)
    if prompt < 0:
        raise TestException(
                f'Didn\'t get prompt (ASCII ENQ) in the device response ({repr(data)})'
            )

    response = data[:prompt]
    if response:
        print(f'Got data before prompt (ASCII ENQ): {repr(response)}. Ignoring...', file=sys.stderr)

    tail = data[prompt+1:]
    if tail:
        print(f'Got data after prompt (ASCII ENQ): {repr(tail)}. Ignoring...', file=sys.stderr)

def command(s, *args):
    s.write(' '.join(args).encode('ascii')+EOL)
    data = s.read_until(ACK)
    if not data:
        raise TestException(
                f'Got timeout while expecting acknowledgement (ASCII ACK) for command "{args[0]}"'
            )

    ack = data.find(ACK)
    if ack:
        raise TestException(
                f'Didn\'t get acknowledgement (ASCII ACK) for command "{args[0]}" in the device '
                f'response ({repr(data)})'
            )

    response = data[:ack]
    if response:
        print(
                f'Got data before acknowledgement (ASCII ACK) for command "{args[0]}": '
                f'{repr(response)}. Ignoring...',
                file=sys.stderr
            )

    data = data[ack+1:]
    data += s.read_until(ENQ)
    if not data:
        raise TestException(
                f'Got timeout while expecting response and prompt (ASCII ENQ) after "{args[0]}" '
                 'command'
            )

    prompt = data.find(ENQ)
    if prompt < 0:
        raise TestException(
                f'Didn\'t get prompt (ASCII ENQ) in the device response to "{args[0]}" command: '
                f'({repr(data)})'
            )

    tail = data[prompt+1:]
    if tail:
        print(
                f'Got data after prompt (ASCII ENQ) in the device response to "{args[0]}" command: '
                f'{repr(tail)}. Ignoring...',
                file=sys.stderr
            )

    return data[:prompt].decode('ascii')

def test(device, baudrate):
    with serial.Serial(sys.argv[1], BAUDRATE, timeout=1, write_timeout=5) as s:
        print('Sending empty command')
        empty_command(s)
        print('Got command prompt')

        print('Sending "test" command')
        response = command(s, 'test', 'first', 'second', 'third')
        print(f'Got response for "test" command:\n{response}')

        print('Sending "help" command')
        response = command(s, 'help')
        print(f'Got response for "help" command:\n{response}')

def main():
    if len(sys.argv) <= 1:
        print('Missing serial interface name. Exiting...', file=sys.stderr)
        return 2

    try:
        test(sys.argv[1], BAUDRATE)
    except TestException as e:
        print(f'{e}. Exiting...', file=sys.stderr)
        return 1

    return 0

if __name__ == '__main__':
    sys.exit(main())
