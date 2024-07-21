#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "pico-con.h"

#define PROG_DESC "A serial console example for Raspberry Pi Pico"

#define INPUT_BUFFER_SIZE 16

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

	if (pico_con_loop(INPUT_BUFFER_SIZE) == 0)
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
