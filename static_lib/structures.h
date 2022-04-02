typedef struct worker {
    char name[20];
    char surname[20];
    char gender[10];
    int age;
    int income;
    char position[20];
    int experience;
} worker;

typedef struct avg_income_for_position {
    char position[20];
    unsigned int num_of_people_on_position;
    float total_income;
    struct avg_income_for_position * next;
} avg_income_for_position;