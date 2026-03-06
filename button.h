#ifndef BUTTON_H
#define BUTTON_H

#include <gtk/gtk.h>
#include <stdbool.h>

typedef struct {
    const char *label;
    const char *icon;       // Icon name (e.g., "document-open")
    const char *css_class;
    bool has_frame;
    bool use_underline;     // Allow Alt+Key shortcuts (e.g., "_File")
    
    // Layout & Expansion
    GtkAlign halign;
    GtkAlign valign;
    bool hexpand;
    bool vexpand;
    int margin_top, margin_bottom, margin_start, margin_end;
    int width;              // Minimum width (-1 for default)
    int height;             // Minimum height (-1 for default)

    // Signals
    void (*on_click)(GtkButton *btn, gpointer user_data);
    gpointer user_data;
} ButtonConfig;

typedef struct {
    const char *label;
    GtkWidget *group_with;  // The other radio button to group this with
    bool is_active;
    const char *css_class;

    // Layout
    GtkAlign halign;
    GtkAlign valign;
    int margin_top, margin_bottom, margin_start, margin_end;

    // Signals
    void (*on_toggled)(GtkToggleButton *btn, gpointer user_data);
    gpointer user_data;
} RadioConfig;

GtkWidget *create_button(ButtonConfig *config);
GtkWidget *create_radio_button(RadioConfig *config);

#endif