#ifndef QUESTION_H
#define QUESTION_H

typedef struct {
    int id;
    char type[10];        // "MCQ" or "4M"
    char difficulty[20];  // "banana", "orange", "jackfruit"
    int marks;
    char question[256];
    char optionA[100];
    char optionB[100];
    char optionC[100];
    char optionD[100];
    char correctOption[10];
} Question;

#endif
