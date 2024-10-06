# pico-con-example

## About

The example demonstrates how to use the pico-con library.

## Submodule

The pico-con library is installed to the project as a submodule. If the project has been just cloned, get the library using `git submodule update --init`.

## Build

Use cmake to build the firmware itself:
```bash
mkdir build
cd build
cmake .. -DPICO_BOARD=pico_w
make
```

Additionally, cmake option `-DCMAKE_BUILD_TYPE=Debug` allows to build debug version and `-DBATCH=1` builds the firmware communicating in the batch mode over serial interface.

## Python Client

While any terminal application can be used to communicate with a device in the human readable mode, for the batch mode test-batch.py script is more convinient. To run it one needs to create a virtual environment:
```bash
python3 -m venv .venv
. .venv/bin/activate
python3 -m pip install -r requirements.txt
```

The script itself takes a serial device name as an argument, for example:
```
./test-batch.py /dev/cu.usbmodem
```
