#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>
#include "question.h"

bool load_questions(const char *filename, Question *questions, int *count);

#endif
