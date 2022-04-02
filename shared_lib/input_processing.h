#include <getopt.h>
#include "structures.h"
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define SUCCESS 1
#define ERROR -1
#define POSITION_MAX_SIZE 20
#define EXPERIENCE_BONUS 2000
#define MAX_SEND_SIZE 100

//need to change it, when time comes
#define NUM_OF_WORKERS 10000

struct mymsgbuf {
    long type;
    char place[MAX_SEND_SIZE];
};

worker ** get_data(FILE * fp);
void *safe_malloc(size_t size);
void push_back(avg_income_for_position * head, worker * employee);
avg_income_for_position * create(worker * employee);
avg_income_for_position * fill_info_needed(worker ** employees);
bool check_if_position_written (avg_income_for_position * positions, char * position);
void add_income_to_category(avg_income_for_position * head, worker * employee);
void send_message(int qid, struct mymsgbuf *qbuf, long type, char * place);
int read_message(int qid, struct mymsgbuf *qbuf, long type);

