#include "input_processing.h"

#define NOT_FOUND -2

void create_report(FILE * fp);
int check_if_exists(char positions[][30], char * pos, int k);
int get_num_of_notes();