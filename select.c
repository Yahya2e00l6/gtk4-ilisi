#include "select.h"

GtkWidget *create_select(select_config *config) {
    if (config == NULL || config->options == NULL) {
        return gtk_drop_down_new(NULL, NULL);
    }

    GtkWidget *dropdown = gtk_drop_down_new_from_strings(config->options);

    if (config->selected_index > 0) {
        gtk_drop_down_set_selected(GTK_DROP_DOWN(dropdown), config->selected_index);
    }

    if (config->css_class && config->css_class[0] != '\0') {
        gtk_widget_add_css_class(dropdown, config->css_class);
    }

    return dropdown;
}