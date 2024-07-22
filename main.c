#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "pico-con.h"

#define PROG_DESC "A serial console example for Raspberry Pi Pico"

#define INPUT_BUFFER_SIZE 255

static int test(size_t argc, char *argv[]);
static int help(size_t argc, char *argv[]);

struct pico_con_command commands[] = {
	{"test", test},
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

int test(size_t argc, char *argv[])
{
	if (argc > 0)
	{
		printf("\"test\" gets %u argument%s:\n", argc, (argc > 1)? "s" : "");
		for (size_t i = 0; i < argc; i++)
		{
			printf("\t%u: \"%s\"\n", i+1, argv[i]);
		}

		return PICO_CON_COMMAND_SUCCESS;
	}

	printf("\"test\" gets no arguments.\n");

	return PICO_CON_COMMAND_SUCCESS;
}

int help(size_t argc, char *argv[])
{
	printf("Available commands:\n"               \
	       "\ttest - prints arguments it gets\n" \
	       "\thelp - prints this message\n\n");
	return PICO_CON_COMMAND_SUCCESS;
}
