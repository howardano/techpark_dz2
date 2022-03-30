typedef struct worker {
    char name[20];
    char surname[20];
    char gender;
    unsigned int age;
    unsigned int income;
    char position[20];
    unsigned int experience;
} worker;

typedef struct avg_income_for_position {
    char position[20];
    unsigned int num_of_people_on_position;
    float total_income;
    struct avg_income_for_position * next;
} avg_income_for_position;