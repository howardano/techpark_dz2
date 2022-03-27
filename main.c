#include <stdio.h>
#include "input_processing.h"

int main(int argc, char *argv[])
{
	printf("Hello World!\n");

	int number_of_processes = process_data(argc, argv);
	printf("processes = %d\n", number_of_processes);
	return 0;
}
