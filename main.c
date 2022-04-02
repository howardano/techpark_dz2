#include "generate_report.h"
#include <time.h>

int main(int argc, char *argv[])
{
	clock_t tStart = clock();
	//printf("Hello World!\n");

	//int number_of_processes = process_data(argc, argv);
	//printf("processes = %d\n", number_of_processes);

	//FILE * fp = fopen("TESTFILE.txt", "r");
	FILE * fp = fopen("workers_BIG.txt", "r");

	//worker ** employees = get_data(fp);

	//avg_income_for_position * positions = fill_info_needed(employees);
	
	create_report(fp);

	printf("Time taken: %fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

	return 0;
}
