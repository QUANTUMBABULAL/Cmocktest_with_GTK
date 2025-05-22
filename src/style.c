#include <gtk/gtk.h>
#include "style.h"

#define BG_COLOR "#23272e"
#define ACCENT_COLOR "#00b894"
#define BTN_HOVER_COLOR "#0984e3"
#define BTN_COLOR "#2d3436"
#define TEXT_COLOR "#dfe6e9"
#define HEADER_COLOR "#00b894"

void set_professional_button(GtkWidget *btn) {
    GtkStyleContext *context = gtk_widget_get_style_context(btn);
    gtk_style_context_add_class(context, "custom-btn");
    gtk_widget_set_name(btn, "custom-btn");
}

void set_professional_label(GtkWidget *lbl, int size, gboolean header) {
    GtkStyleContext *context = gtk_widget_get_style_context(lbl);
    gtk_style_context_add_class(context, header ? "header-label" : "main-label");
    gtk_widget_set_name(lbl, header ? "header-label" : "main-label");
    char css[128];
    snprintf(css, sizeof(css),
        "#%s { font-family: 'Segoe UI', 'Arial', 'Sans'; font-size: %dpt; color: %s; font-weight: %s; }",
        header ? "header-label" : "main-label", size, header ? HEADER_COLOR : TEXT_COLOR, header ? "bold" : "normal");
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}

void apply_global_css(void) {
    const char *css =
        "window { background: " BG_COLOR "; }"
        "#custom-btn {"
        "  background: " BTN_COLOR ";"
        "  color: " ACCENT_COLOR ";"
        "  border-radius: 12px;"
        "  font-family: 'Segoe UI', 'Arial', 'Sans';"
        "  font-size: 18pt;"
        "  padding: 12px 0;"
        "  transition: background 200ms;"
        "}"
        "#custom-btn:hover {"
        "  background: " BTN_HOVER_COLOR ";"
        "  color: #fff;"
        "}";
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
    g_object_unref(provider);
}