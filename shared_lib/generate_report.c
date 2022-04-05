#include "generate_report.h"

int get_num_of_notes() {
    FILE * fp = fopen("buf_file.txt", "r");
    int num_of_notes = 0;
	size_t len = 0;
	char * line;

    while ((getline(&line, &len, fp)) > 0) {
        num_of_notes++;
    }

    fclose(fp);
    return num_of_notes;
}

int check_if_exists(char positions[][30], char * pos, int k) {
    for (int i = 0; i < k; i++) {
        if (strcmp(positions[i], pos) == 0) {
            return i;
        }
    }
    return NOT_FOUND;
}

void create_report(FILE * fp) {
    if (!fp) {
        printf("Error opening file!\n");
        exit(1);
    }
    worker ** employees = get_data(fp);
    fclose(fp);

    fill_info_needed(employees);

    fp = fopen("buf_file.txt", "r");
    int num_of_notes = get_num_of_notes();
    char position[num_of_notes][30];
    int num_of_people[num_of_notes];
    float incomes[num_of_notes];

    int index_position;
	size_t len = 0;
	char * line;

    size_t len_sp = 0;
    char * line_sp;

    int k = 0;
    int people = 0;
    float inc = 0;
    char pos[20];

    int people_sp = 0;
    float inc_sp = 0;
    char pos_sp[20];

    getline(&line_sp, &len_sp, fp);
    sscanf(line_sp, "%19s%f%d", pos_sp, &inc_sp, &people_sp);

    char special_pos[20];
    strcpy(special_pos, pos_sp);
    float max_inc = inc_sp;
    int max_people = people_sp;

    for (int i = 0; i < num_of_notes; ++i) {
        getline(&line_sp, &len_sp, fp);
        sscanf(line_sp, "%19s%f%d", pos_sp, &inc_sp, &people_sp);
        if (strcmp(pos_sp, special_pos) == 0) {
            if (max_inc < inc_sp) {
                max_inc = inc_sp;
            }
            if (max_people < people_sp) {
                max_people = people_sp;
            }
        }
    }
    strcpy(position[k], special_pos);
    incomes[k] = max_inc;
    num_of_people[k] = max_people;
    k++;
    fclose(fp);

    fp = fopen("buf_file.txt", "r");
    getline(&line, &len, fp);
    sscanf(line, "%19s%f%d", pos, &inc, &people);

    for (int i = 0; i < num_of_notes-1; ++i) {
        getline(&line, &len, fp);
        sscanf(line, "%19s%f%d", pos, &inc, &people);
        if ((index_position = check_if_exists(position, pos, k)) == NOT_FOUND && strcmp(pos, special_pos) != 0) {
            strcpy(position[k], pos);
            num_of_people[k] = people;
            incomes[k] = inc;
            k++;
        } else {
            if (strcmp(pos, special_pos) != 0) {
                num_of_people[index_position] += people;
                incomes[index_position] += inc;
            }
        }
    }
    fclose(fp);

    fp = fopen("report.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < k; ++i) {
        fprintf(fp, "%s\t%f\n", position[i], incomes[i] / num_of_people[i]);
    }

    fclose(fp);
}

