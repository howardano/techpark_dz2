#include "generate_report_static.h"

int main(int argc, char *argv[])
{
	//printf("Hello World!\n");

	//int number_of_processes = process_data(argc, argv);
	//printf("processes = %d\n", number_of_processes);

	FILE * fp = fopen("TESTFILE.txt", "r");

	worker ** employees = get_data(fp);

	avg_income_for_position * positions = fill_info_needed(employees);
	
	generate_report(positions);

	return 0;
}
