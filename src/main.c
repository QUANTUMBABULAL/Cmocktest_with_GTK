#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "file_utils.h"
#include "generator.h"
#include "quiz.h"
#include "style.h"

static Question questions[1000];
static int question_count = 0;
static char selected_difficulty[20] = "";

static GtkWidget *home_window = NULL;

static void generate_and_show(GtkWidget *widget, gpointer user_data) {
    const char *type = (const char *)user_data;
    char *output = generate_paper_to_string(selected_difficulty, type, questions, question_count);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Generated Question Paper");
    gtk_window_fullscreen(GTK_WINDOW(window));
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *heading = gtk_label_new("QUESTION PAPER GENERATOR USING C");
    set_professional_label(heading, 48, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), heading, FALSE, FALSE, 0);

    GtkWidget *fruit_lbl = gtk_label_new(selected_difficulty);
    set_professional_label(fruit_lbl, 32, FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), fruit_lbl, FALSE, FALSE, 0);

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_vexpand(scrolled_window, TRUE);
    gtk_widget_set_hexpand(scrolled_window, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    GtkWidget *text_view = gtk_text_view_new();
    set_professional_label(text_view, 22, FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);

    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    if (output) {
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
        gtk_text_buffer_set_text(buffer, output, -1);
        free(output);
    }

    GtkWidget *exit_btn = gtk_button_new_with_label("🏠 Go to Home");
    gtk_widget_set_size_request(exit_btn, 300, 60);
    set_professional_button(exit_btn);
    gtk_box_pack_start(GTK_BOX(vbox), exit_btn, FALSE, FALSE, 20);

    g_signal_connect_swapped(exit_btn, "clicked", G_CALLBACK(gtk_widget_show_all), home_window);
    g_signal_connect_swapped(exit_btn, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    gtk_widget_show_all(window);
}

typedef struct {
    Question *questions;
    int question_count;
    const char *difficulty;
    GtkWidget *home_window;
} QuizArgs;

static void start_quiz_wrapper(GtkWidget *widget, gpointer user_data) {
    QuizArgs *args = (QuizArgs *)user_data;
    start_quiz(args->questions, args->question_count, args->difficulty, args->home_window);
    free(args);
}

static void show_type_window(GtkWidget *widget, gpointer data) {
    strcpy(selected_difficulty, (const char *)data);

    GtkWidget *type_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(type_window), "Select Question Type");
    gtk_window_fullscreen(GTK_WINDOW(type_window));
    gtk_window_set_position(GTK_WINDOW(type_window), GTK_WIN_POS_CENTER);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
    gtk_container_add(GTK_CONTAINER(type_window), vbox);
    gtk_widget_set_halign(vbox, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);

    GtkWidget *fruit_lbl = gtk_label_new(selected_difficulty);
    set_professional_label(fruit_lbl, 32, FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), fruit_lbl, FALSE, FALSE, 10);

    GtkWidget *label = gtk_label_new("Select Question Type:");
    set_professional_label(label, 24, FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 10);

    const char *labels[] = {"Only MCQs", "Only 4 Markers", "Both", "Take Quiz"};
    const char *types[] = {"mcq", "desc", "both", "quiz"};

    for (int i = 0; i < 4; ++i) {
        GtkWidget *btn = gtk_button_new_with_label(labels[i]);
        gtk_widget_set_size_request(btn, 400, 80);
        set_professional_button(btn);
        gtk_box_pack_start(GTK_BOX(vbox), btn, TRUE, TRUE, 0);

        if (i == 3) {
            QuizArgs *args = malloc(sizeof(QuizArgs));
            args->questions = questions;
            args->question_count = question_count;
            args->difficulty = selected_difficulty;
            args->home_window = home_window;
            g_signal_connect(btn, "clicked", G_CALLBACK(start_quiz_wrapper), args);
        } else {
            g_signal_connect(btn, "clicked", G_CALLBACK(generate_and_show), (gpointer)types[i]);
        }
    }

    gtk_widget_show_all(type_window);
    gtk_widget_hide(home_window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    apply_global_css();
    srand(time(NULL));

    if (!load_questions("data/questions.csv", questions, &question_count)) {
        g_printerr("❌ Failed to load questions\n");
        return 1;
    }

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Question Generator");
    gtk_window_fullscreen(GTK_WINDOW(window));
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 40);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_set_halign(vbox, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);

    GtkWidget *heading = gtk_label_new("QUESTION PAPER GENERATOR");
    set_professional_label(heading, 40, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), heading, FALSE, FALSE, 10);

    GtkWidget *label = gtk_label_new("Select Difficulty:");
    set_professional_label(label, 24, FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 10);

    const char *diffs[] = {"🍌 Banana (Easy)", "🍊 Orange (Medium)", "🥭 Jackfruit (Hard)"};
    const char *levels[] = {"easy", "medium", "hard"};

    for (int i = 0; i < 3; ++i) {
        GtkWidget *btn = gtk_button_new_with_label(diffs[i]);
        gtk_widget_set_size_request(btn, 400, 100);
        set_professional_button(btn);
        gtk_box_pack_start(GTK_BOX(vbox), btn, TRUE, TRUE, 0);
        g_signal_connect(btn, "clicked", G_CALLBACK(show_type_window), (gpointer)levels[i]);
    }

    home_window = window;
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}