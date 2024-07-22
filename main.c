#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "pico-con.h"

#define PROG_DESC "A serial console example for Raspberry Pi Pico"

#define INPUT_BUFFER_SIZE 16

static int help(void);

struct pico_con_command commands[] = {
	{"help", help},
	{NULL, NULL},
};

int main()
{
	bi_decl(bi_program_description(PROG_DESC));

	stdio_init_all();

	int n = 0;
	while (n < 10)
	{
		sleep_ms(1000);
		n++;
		putchar('.');
	}

	printf("\n" PROG_DESC "\n");

	if (pico_con_loop(commands, INPUT_BUFFER_SIZE) == 0)
	{
		printf("Serial console closed.\n");
	}
	else
	{
		printf("Failed to run serial console.\n");
	}

	while (1)
	{
		tight_loop_contents();
	}
}

int help(void)
{
	printf("Available commands:\n\n" \
	       "\thelp - prints this message.\n\n");
	return PICO_CON_COMMAND_SUCCESS;
}
