#ifndef BUTTON_H
#define BUTTON_H

#include <gtk/gtk.h>
#include <stdbool.h>

typedef struct {
    const char *label;
    const char *icon;       // Use icon-name strings
    const char *css_class;
    bool has_frame;
    bool use_underline;
    GtkAlign halign;
    GtkAlign valign;
    bool hexpand;
    bool vexpand;
    int margin_top, margin_bottom, margin_start, margin_end;
    int width, height;      // Request size

    void (*on_click)(GtkButton *btn, gpointer user_data);
    gpointer user_data;
} ButtonConfig;

typedef struct {
    const char *label;
    GtkWidget *group_with;  // Must be a GtkCheckButton in GTK 4
    bool is_active;
    
    // Layout
    GtkAlign halign;
    GtkAlign valign;
    int margin_top, margin_bottom;

    void (*on_toggled)(GtkCheckButton *btn, gpointer user_data);
    gpointer user_data;
} RadioConfig;

GtkWidget *create_button(ButtonConfig *config);
GtkWidget *create_radio_button(RadioConfig *config);

#endif