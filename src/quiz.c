#include "quiz.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUESTIONS 10

static int current_index = 0;
static int score = 0;
static int total_questions = 0;
static Question selected_questions[MAX_QUESTIONS];
static GtkWidget *quiz_window;
static GtkWidget *home_window_global;
static GtkWidget *question_label;
static GtkWidget *option_buttons[4];
static GtkWidget *score_label;

static void set_hacker_style(GtkWidget *widget, int font_size) {
    char font_str[64];
    snprintf(font_str, sizeof(font_str), "Monospace Bold %d", font_size);
    gtk_widget_override_font(widget, pango_font_description_from_string(font_str));
    gtk_widget_override_background_color(widget, GTK_STATE_FLAG_NORMAL, &(GdkRGBA){0,0,0,1});
    gtk_widget_override_color(widget, GTK_STATE_FLAG_NORMAL, &(GdkRGBA){0,1,0,1});
}

static void show_result() {
    char result[128];
    snprintf(result, sizeof(result), "✅ QUIZ COMPLETED!\nYour Score: %d / %d", score, total_questions);
    gtk_label_set_text(GTK_LABEL(score_label), result);
}

static void load_question() {
    if (current_index >= total_questions) {
        show_result();
        for (int i = 0; i < 4; i++)
            gtk_widget_hide(option_buttons[i]);
        return;
    }

    Question *q = &selected_questions[current_index];

    char question_text[512];
    snprintf(question_text, sizeof(question_text), "Q%d. %s", current_index + 1, q->question);
    gtk_label_set_text(GTK_LABEL(question_label), question_text);

    const char *opts[] = {q->optionA, q->optionB, q->optionC, q->optionD};
    for (int i = 0; i < 4; i++) {
        gtk_button_set_label(GTK_BUTTON(option_buttons[i]), opts[i]);
        gtk_widget_set_sensitive(option_buttons[i], TRUE);
        gtk_widget_show(option_buttons[i]);
    }

    gtk_label_set_text(GTK_LABEL(score_label), "");
}

static void option_selected(GtkWidget *widget, gpointer user_data) {
    int selected = GPOINTER_TO_INT(user_data);
    Question *q = &selected_questions[current_index];

    // If correctOption is 'A', 'B', 'C', 'D' in CSV, convert to 0-based index
    int correct = 0;
    if (q->correctOption[0] == 'A') correct = 0;
    else if (q->correctOption[0] == 'B') correct = 1;
    else if (q->correctOption[0] == 'C') correct = 2;
    else if (q->correctOption[0] == 'D') correct = 3;

    if (selected == correct)
        score++;

    current_index++;
    load_question();
}

static void return_home(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(quiz_window);
    gtk_widget_show_all(home_window_global);
}

extern void set_professional_button(GtkWidget *btn);
extern void set_professional_label(GtkWidget *lbl, int size, gboolean header);
extern void apply_global_css(void);

void start_quiz(Question *questions, int question_count, const char *difficulty, GtkWidget *home_window) {
    home_window_global = home_window;

    // Filter MCQs only for the selected difficulty
    Question mcq_pool[1000];
    int mcq_count = 0;
    for (int i = 0; i < question_count; i++) {
        if (strcmp(questions[i].type, "mcq") == 0 && strcmp(questions[i].difficulty, difficulty) == 0)
            mcq_pool[mcq_count++] = questions[i];
    }

    if (mcq_count < MAX_QUESTIONS) total_questions = mcq_count;
    else total_questions = MAX_QUESTIONS;

    // Shuffle for unique questions
    srand(time(NULL));
    for (int i = mcq_count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Question temp = mcq_pool[i];
        mcq_pool[i] = mcq_pool[j];
        mcq_pool[j] = temp;
    }
    for (int i = 0; i < total_questions; i++) {
        selected_questions[i] = mcq_pool[i];
    }

    current_index = 0;
    score = 0;

    // Apply CSS if not already done
    apply_global_css();

    quiz_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(quiz_window), "Take a Quiz");
    gtk_window_fullscreen(GTK_WINDOW(quiz_window));
    gtk_window_set_position(GTK_WINDOW(quiz_window), GTK_WIN_POS_CENTER);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
    gtk_container_add(GTK_CONTAINER(quiz_window), vbox);
    gtk_widget_set_halign(vbox, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);

    GtkWidget *heading = gtk_label_new("🧠 MCQ QUIZ MODE");
    set_professional_label(heading, 36, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), heading, FALSE, FALSE, 10);

    question_label = gtk_label_new("");
    set_professional_label(question_label, 24, FALSE);
    gtk_label_set_line_wrap(GTK_LABEL(question_label), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), question_label, FALSE, FALSE, 10);

    for (int i = 0; i < 4; i++) {
        option_buttons[i] = gtk_button_new_with_label("Option");
        gtk_widget_set_size_request(option_buttons[i], 600, 60);
        set_professional_button(option_buttons[i]);
        gtk_box_pack_start(GTK_BOX(vbox), option_buttons[i], FALSE, FALSE, 5);
        g_signal_connect(option_buttons[i], "clicked", G_CALLBACK(option_selected), GINT_TO_POINTER(i));
    }

    score_label = gtk_label_new("");
    set_professional_label(score_label, 24, FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), score_label, FALSE, FALSE, 20);

    GtkWidget *home_btn = gtk_button_new_with_label("🏠 Return Home");
    gtk_widget_set_size_request(home_btn, 300, 50);
    set_professional_button(home_btn);
    gtk_box_pack_start(GTK_BOX(vbox), home_btn, FALSE, FALSE, 10);
    g_signal_connect(home_btn, "clicked", G_CALLBACK(return_home), NULL);

    gtk_widget_show_all(quiz_window);
    gtk_widget_hide(home_window_global);

    load_question();
}
