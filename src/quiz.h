#ifndef QUIZ_H
#define QUIZ_H

#include <gtk/gtk.h>
#include "question.h"

void start_quiz(Question *questions, int question_count, const char *difficulty, GtkWidget *home_window);

#endif
