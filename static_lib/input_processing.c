//  Copyright (c) 2016 Microsoft Corporation. All rights reserved.
//  Licensed under the MIT License.
//  See License file in the project root for license information.

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
    if (getline(&line, &len, fp) == 0) {
      exit(ERROR);
    }
    employees[i] = (worker*) safe_malloc(sizeof(worker));
    sscanf(line, "%20s%20s%20s%d%d%20s%d",
    &employees[i]->name, &employees[i]->surname, &employees[i]->gender,
    &employees[i]->age, &employees[i]->income, &employees[i]->position,
    &employees[i]->experience);
  }

  return employees;
}

avg_income_for_position * create(worker * employee) {
  avg_income_for_position *tmp = (avg_income_for_position *)
                            safe_malloc(sizeof(avg_income_for_position));
  strncpy(tmp->position, employee->position,
                        sizeof(tmp->position));
  tmp->total_income = employee->experience * EXPERIENCE_BONUS +
                        employee->income;
  tmp->num_of_people_on_position = 1;
  tmp->next = NULL;
  return(tmp);
}

void push_back(avg_income_for_position * head, worker * employee) {
  avg_income_for_position * tmp = (avg_income_for_position*)
                            safe_malloc(sizeof(avg_income_for_position));
  strncpy(tmp->position, employee->position, sizeof(tmp->position));
  tmp->num_of_people_on_position = 1;
  tmp->total_income = employee->experience * EXPERIENCE_BONUS +
                        employee->income;
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
      tmp->total_income += employee->experience * EXPERIENCE_BONUS +
                        employee->income;
      break;
    }
    tmp = tmp->next;
  }
}

bool check_if_position_written(avg_income_for_position * positions,
                                char * position) {
  avg_income_for_position * ptr = positions;

  while (ptr != NULL) {
    if (strcmp(ptr->position, position) == 0) {
      return true;
    }
    ptr = ptr->next;
  }
  return false;
}

avg_income_for_position * fill_info_needed(worker ** employees) {
  avg_income_for_position * positions = create(employees[0]);

  for (int i = 1; i < NUM_OF_WORKERS; ++i) {
    if (!check_if_position_written(positions, employees[i]->position)) {
      push_back(positions, employees[i]);
    } else {
      add_income_to_category(positions, employees[i]);
    }
  }

  return positions;
}

