#ifndef STYLE_H
#define STYLE_H

#include <gtk/gtk.h>

void apply_global_css(void);
void set_professional_button(GtkWidget *btn);
void set_professional_label(GtkWidget *lbl, int size, gboolean header);

#endif