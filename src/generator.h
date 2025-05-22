#ifndef GENERATOR_H
#define GENERATOR_H

#include "question.h"

// Shuffle question array
void shuffle(Question *arr, int n);

// Generate question paper as a string (for GTK display)
char* generate_paper_to_string(const char *difficulty, const char *type, Question *questions, int total);

#endif  // GENERATOR_H
