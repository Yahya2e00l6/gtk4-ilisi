#include "input.h"

GtkWidget *create_input(input_config *config) {
    GtkWidget *entry = gtk_entry_new();

    // 1. Text & Placeholder
    if (config->default_text) {
        gtk_entry_set_text(GTK_ENTRY(entry), config->default_text);
    }
    if (config->placeholder) {
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry), config->placeholder);
    }

    // 2. Security & Constraints
    gtk_entry_set_visibility(GTK_ENTRY(entry), !config->is_password);
    if (config->max_length > 0) {
        gtk_entry_set_max_length(GTK_ENTRY(entry), config->max_length);
    }
    gtk_editable_set_editable(GTK_EDITABLE(entry), config->is_editable);

    // 3. Behavior & Display
    gtk_entry_set_input_purpose(GTK_ENTRY(entry), config->purpose);
    gtk_entry_set_alignment(GTK_ENTRY(entry), config->xalign);
    gtk_entry_set_has_frame(GTK_ENTRY(entry), config->has_frame);

    // 4. Common Widget Layout
    gtk_widget_set_halign(entry, config->halign);
    gtk_widget_set_valign(entry, config->valign);
    gtk_widget_set_hexpand(entry, config->hexpand);
    gtk_widget_set_margin_top(entry, config->margin_top);
    gtk_widget_set_margin_bottom(entry, config->margin_bottom);
    gtk_widget_set_margin_start(entry, config->margin_start);
    gtk_widget_set_margin_end(entry, config->margin_end);

    if (config->css_class) {
        gtk_style_context_add_class(gtk_widget_get_style_context(entry), config->css_class);
    }

    // 5. Signal Connections
    if (config->on_change) {
        g_signal_connect(entry, "changed", G_CALLBACK(config->on_change), config->user_data);
    }
    if (config->on_activate) {
        g_signal_connect(entry, "activate", G_CALLBACK(config->on_activate), config->user_data);
    }

    return entry;
}

GtkWidget *create_select(select_config *config) {
    GtkWidget *combo;

    // 1. Initialize (With or without a text entry field)
    if (config->has_entry) {
        combo = gtk_combo_box_text_new_with_entry();
    } else {
        combo = gtk_combo_box_text_new();
    }

    // 2. Add Options
    if (config->options) {
        for (int i = 0; config->options[i] != NULL; i++) {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), config->options[i]);
        }
    }

    // 3. Set Default Selection
    if (config->selected_index >= 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo), config->selected_index);
    }

    // 4. Layout & Margins
    gtk_widget_set_halign(combo, config->halign);
    gtk_widget_set_valign(combo, config->valign);
    gtk_widget_set_hexpand(combo, config->hexpand);
    gtk_widget_set_vexpand(combo, config->vexpand);
    
    gtk_widget_set_margin_top(combo, config->margin_top);
    gtk_widget_set_margin_bottom(combo, config->margin_bottom);
    gtk_widget_set_margin_start(combo, config->margin_start);
    gtk_widget_set_margin_end(combo, config->margin_end);

    // 5. CSS Styling
    if (config->css_class) {
        gtk_style_context_add_class(gtk_widget_get_style_context(combo), config->css_class);
    }

    // 6. Signal Connection (The "Action")
    if (config->on_change) {
        g_signal_connect(combo, "changed", G_CALLBACK(config->on_change), config->user_data);
    }

    return combo;
}

void my_select_handler(GtkComboBox *combo, gpointer data) {
    char *selected_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
    g_print("User selected: %s\n", selected_text);
    g_free(selected_text); 
}