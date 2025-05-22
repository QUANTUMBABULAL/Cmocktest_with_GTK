#include "file_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool load_questions(const char *filename, Question *questions, int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) return false;

    char line[1024];
    *count = 0;

    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file)) {
        if (*count >= 1000) break;

        Question *q = &questions[*count];
        char *token = strtok(line, ",");
        if (!token) continue;
        q->id = atoi(token);

        token = strtok(NULL, ",");
        strncpy(q->type, token ? token : "", sizeof(q->type));

        token = strtok(NULL, ",");
        strncpy(q->difficulty, token ? token : "", sizeof(q->difficulty));

        token = strtok(NULL, ",");
        q->marks = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        strncpy(q->question, token ? token : "", sizeof(q->question));

        token = strtok(NULL, ",");
        strncpy(q->optionA, token ? token : "", sizeof(q->optionA));

        token = strtok(NULL, ",");
        strncpy(q->optionB, token ? token : "", sizeof(q->optionB));

        token = strtok(NULL, ",");
        strncpy(q->optionC, token ? token : "", sizeof(q->optionC));

        token = strtok(NULL, ",");
        strncpy(q->optionD, token ? token : "", sizeof(q->optionD));

        token = strtok(NULL, ",\n");
        strncpy(q->correctOption, token ? token : "", sizeof(q->correctOption));

        (*count)++;
    }

    fclose(file);
    return true;
}
