#include "generate_report_static.h"

void test_fun() {
    printf("You made it to your static library!\n");
}

void generate_report(avg_income_for_position * positions) {
    FILE *fp = fopen("report.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    avg_income_for_position * ptr = positions;

    while(ptr != NULL) {
        fprintf(fp, "%s\t%f\n", ptr->position, ptr->total_income / ptr->num_of_people_on_position);
        ptr = ptr->next;
    }

    fclose(fp);
}