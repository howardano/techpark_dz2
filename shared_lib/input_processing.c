#include "input_processing.h"

void *safe_malloc(size_t size) {
  if (size == 0) {
      return NULL;
  }
  void *ptr = malloc(size);
  return ptr;
}

worker ** get_data(FILE * fp) {
	size_t len = 0;
	char * line;

  worker ** employees = (worker**) safe_malloc(NUM_OF_WORKERS * sizeof(worker));

	for (int i = 0; i < NUM_OF_WORKERS; ++i) {
		getline(&line, &len, fp);
		employees[i] = (worker*) safe_malloc(sizeof(worker));
    //employees[i] = (worker*) mmap(NULL, sizeof(worker), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
		sscanf(line, "%20s%20s%20s%d%d%20s%d", 
		&employees[i]->name, &employees[i]->surname, &employees[i]->gender, 
		&employees[i]->age, &employees[i]->income, &employees[i]->position,
		&employees[i]->experience);
	}

  return employees;
}

avg_income_for_position * create(worker * employee) {
  avg_income_for_position *tmp = (avg_income_for_position *)safe_malloc(sizeof(avg_income_for_position));
  //avg_income_for_position *tmp = (avg_income_for_position *) mmap(NULL, sizeof(avg_income_for_position), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  strncpy(tmp->position, employee->position, sizeof(tmp->position));
  tmp->total_income = employee->experience * EXPERIENCE_BONUS + employee->income;
  tmp->num_of_people_on_position = 1;
  tmp->next = NULL;
  return(tmp);
}

void push_back(avg_income_for_position * head, worker * employee) {
  avg_income_for_position * tmp = (avg_income_for_position*) safe_malloc(sizeof(avg_income_for_position));
  //avg_income_for_position * tmp = (avg_income_for_position*) mmap(NULL, sizeof(avg_income_for_position), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  strncpy(tmp->position, employee->position, sizeof(tmp->position));
  tmp->num_of_people_on_position = 1;
  tmp->total_income = employee->experience * EXPERIENCE_BONUS + employee->income;
  tmp->next = NULL;

  avg_income_for_position *ptr = head;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = tmp;
}

void add_income_to_category(avg_income_for_position * head, worker * employee) {
  avg_income_for_position * tmp = head;
  while (tmp != NULL) {
    if (strcmp(tmp->position, employee->position) == 0) {
      tmp->num_of_people_on_position++;
      tmp->total_income += employee->experience * EXPERIENCE_BONUS + employee->income;
      break;
    }
    tmp = tmp->next;
  }
}

bool check_if_position_written (avg_income_for_position * positions, char * position) {
  avg_income_for_position * ptr = positions;

  while (ptr != NULL) {
    if(strcmp(ptr->position, position) == 0) {
      return true;
    }
    ptr = ptr->next;
  }
  return false;
}

void send_message(int qid, struct mymsgbuf *qbuf, long type, char * place) {
  qbuf->type = type;
  strncpy(qbuf->place, place, sizeof(qbuf->place));
  if(msgsnd(qid, (struct msgbuf *)qbuf, strlen(qbuf->place)+1, 0) == -1) {
    exit(ERROR);
  }
}

int read_message(int qid, struct mymsgbuf *qbuf, long type) {
  qbuf->type = type;
  msgrcv(qid, (struct msgbuf *)qbuf, MAX_SEND_SIZE, type, 0);
  return atoi(qbuf->place);
}

avg_income_for_position * fill_info_needed(worker ** employees) {
  avg_income_for_position * positions = create(employees[0]);
  int n_pr = 100;
  int m[n_pr];

  float b_size = NUM_OF_WORKERS / (n_pr); 
  m[0] = 1;
  for (int i = 1; i < n_pr; i++) {
    m[i] = m[i-1] + b_size;
  }

  int qtype = 1, stat, pid[n_pr], msgqid;
  struct mymsgbuf qbuf;
  key_t key = 7777;

  pid[0] = getpid();
  if ((msgqid = msgget(key, IPC_CREAT|0660)) == -1) {
    exit(ERROR);
  }

  char str[MAX_SEND_SIZE];
  sprintf(str, "%d", m[0]);
  send_message(msgqid, &qbuf, qtype, str);

  int place = 0;
  
  for (int i = 0; i < n_pr-1; ++i) {
    if((pid[i+1] = fork()) == -1) {
      exit(ERROR);
    }
    if(pid[i+1] == 0) {
      place = 1;
      char str[MAX_SEND_SIZE];
      sprintf(str, "%d", m[i+1]);
      send_message(msgqid, &qbuf, qtype, str);
      break;
    }
  }
  place = read_message(msgqid, &qbuf, qtype);

  int begin = place;
  int end = begin + b_size;

  if(begin + b_size > NUM_OF_WORKERS) {
    end = NUM_OF_WORKERS;
  }

  for (int i = begin; i < end; ++i) {
    if(!check_if_position_written(positions, employees[i]->position)) {
      push_back(positions, employees[i]);
    } else {
      add_income_to_category(positions, employees[i]);
    }
  }

  FILE * fp = fopen("buf_file.txt", "a");
  avg_income_for_position * ptr = positions;

  while(ptr != NULL) {
    fprintf(fp, "%s\t%f\t%d\n", ptr->position, ptr->total_income, ptr->num_of_people_on_position);
    ptr = ptr->next;
  }

  fclose(fp);

  if(getpid() != pid[0]) {
    exit(SUCCESS);
  }

  for (int i = 1; i < n_pr; ++i) {
     waitpid(-1, &stat, 0);
  }

  return positions;
}