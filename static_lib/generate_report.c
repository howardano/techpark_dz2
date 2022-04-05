//  Copyright (c) 2016 Microsoft Corporation. All rights reserved.
//  Licensed under the MIT License.
//  See License file in the project root for license information.

#include "generate_report.h"

void create_report(FILE * fp) {
    if (!fp) {
        printf("Error opening file!\n");
        exit(ERROR);
    }
    worker ** employees = get_data(fp);
    fclose(fp);

    avg_income_for_position * positions = fill_info_needed(employees);

    fp = fopen("report.txt", "w");
    avg_income_for_position * ptr = positions;

    while (ptr != NULL) {
        fprintf(fp, "%s\t%f\n",
        ptr->position,
        ptr->total_income / ptr->num_of_people_on_position);

        ptr = ptr->next;
    }

    fclose(fp);
}

