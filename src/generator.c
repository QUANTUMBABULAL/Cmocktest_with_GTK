#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Shuffle the array randomly
void shuffle(Question *arr, int n) {
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Question temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Generate the question paper in memory (as a single string)
char* generate_paper_to_string(const char *difficulty, const char *type, Question *questions, int total) {
    Question selected[100];
    int sel_count = 0;

    // Filter by difficulty and type
    for (int i = 0; i < total; ++i) {
        if (strcmp(questions[i].difficulty, difficulty) == 0 &&
            (strcmp(type, "both") == 0 || strcmp(questions[i].type, type) == 0)) {
            selected[sel_count++] = questions[i];
        }
    }

    if (sel_count == 0) return NULL;

    shuffle(selected, sel_count);

    // Allocate a big enough buffer for the full question paper
    char *buffer = malloc(8192);  // you can increase size if needed
    if (!buffer) return NULL;
    buffer[0] = '\0';  // start empty

    int mcq_count = 0, desc_count = 0;
    char line[1024];

    for (int i = 0; i < sel_count; ++i) {
        if (strcmp(selected[i].type, "mcq") == 0 && mcq_count < 24 &&
            (strcmp(type, "mcq") == 0 || strcmp(type, "both") == 0)) {

            snprintf(line, sizeof(line),
                "Q%d (MCQ - %d mark): %s\nA. %s\nB. %s\nC. %s\nD. %s\n\n",
                mcq_count + 1, selected[i].marks, selected[i].question,
                selected[i].optionA, selected[i].optionB, selected[i].optionC, selected[i].optionD);

            strncat(buffer, line, 8192 - strlen(buffer) - 1);
            mcq_count++;

        } else if (strcmp(selected[i].type, "desc") == 0 && desc_count < 4 &&
                   (strcmp(type, "desc") == 0 || strcmp(type, "both") == 0)) {

            snprintf(line, sizeof(line), "Q%d (4 Marks): %s\n\n", 25 + desc_count, selected[i].question);

            strncat(buffer, line, 8192 - strlen(buffer) - 1);
            desc_count++;
        }

        if ((strcmp(type, "mcq") == 0 && mcq_count >= 24) ||
            (strcmp(type, "desc") == 0 && desc_count >= 4) ||
            (strcmp(type, "both") == 0 && mcq_count >= 24 && desc_count >= 4)) {
            break;
        }
    }

    return buffer;
}
