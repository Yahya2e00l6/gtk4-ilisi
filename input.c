#include "input.h"

GtkWidget *create_input(input_config *config) {
    GtkWidget *entry = gtk_entry_new();
    
    if (config == NULL) {
        return entry;
    }

    if (config->placeholder) {
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry), config->placeholder);
    }
    
    if (config->default_text) {
        gtk_editable_set_text(GTK_EDITABLE(entry), config->default_text);
    }
    
    if (config->is_password) {
        gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
    }
    
    if (config->max_length > 0) {
        gtk_entry_set_max_length(GTK_ENTRY(entry), config->max_length);
    }

    if (config->css_class && config->css_class[0] != '\0') {
        gtk_widget_add_css_class(entry, config->css_class);
    }

    return entry;
}