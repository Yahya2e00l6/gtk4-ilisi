#ifndef INPUT_H
#define INPUT_H
#include <gtk/gtk.h>
#include <stdbool.h>

typedef struct {
    const char *placeholder;
    const char *default_text;
    const char *css_class;
    bool is_password;
    int max_length;
    bool is_editable;
    GtkInputPurpose purpose;
    float xalign;
    bool has_frame;
    GtkAlign halign;
    GtkAlign valign;
    bool hexpand;
    int margin_top, margin_bottom, margin_start, margin_end;
    void (*on_change)(GtkEditable *editable, gpointer user_data);
    void (*on_activate)(GtkEntry *entry, gpointer user_data);
    gpointer user_data;
} input_config;

typedef struct {
    const char **options;
    int selected_index;
    const char *css_class;
    bool has_entry;
    const char *id_column;

    GtkAlign halign;
    GtkAlign valign;
    bool hexpand;
    bool vexpand;
    int margin_top, margin_bottom, margin_start, margin_end;
    void (*on_change)(GtkComboBox *combo, gpointer user_data);
    gpointer user_data;
} select_config;

GtkWidget *create_input(input_config *config);
GtkWidget *create_select(select_config *config);
void my_select_handler(GtkComboBox *combo, gpointer data);
#endif