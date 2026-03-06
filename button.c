#include "button.h"

GtkWidget *create_button(ButtonConfig *config) {
    GtkWidget *button;

    // 1. Create the button
    if (config->label && config->use_underline) {
        button = gtk_button_new_with_mnemonic(config->label);
    } else if (config->label) {
        button = gtk_button_new_with_label(config->label);
    } else {
        button = gtk_button_new();
    }
    if (config->icon) {
        gtk_button_set_icon_name(GTK_BUTTON(button), config->icon);
    }
    // 3. Styling & Layout
    gtk_button_set_has_frame(GTK_BUTTON(button), config->has_frame);
    
    if (config->css_class) {
        gtk_widget_add_css_class(button, config->css_class);
    }

    gtk_widget_set_halign(button, config->halign);
    gtk_widget_set_valign(button, config->valign);
    gtk_widget_set_hexpand(button, config->hexpand);
    gtk_widget_set_vexpand(button, config->vexpand);
    
    if (config->width > 0 || config->height > 0) {
        gtk_widget_set_size_request(button, config->width, config->height);
    }

    gtk_widget_set_margin_top(button, config->margin_top);
    gtk_widget_set_margin_bottom(button, config->margin_bottom);
    gtk_widget_set_margin_start(button, config->margin_start);
    gtk_widget_set_margin_end(button, config->margin_end);

    // 4. Signal Connection
    if (config->on_click) {
        g_signal_connect(button, "clicked", G_CALLBACK(config->on_click), config->user_data);
    }

    return button;
}

GtkWidget *create_radio_button(RadioConfig *config) {
    GtkWidget *radio = gtk_check_button_new_with_label(config->label);
    
    // Set as a radio button by joining a group
    if (config->group_with) {
        gtk_check_button_set_group(GTK_CHECK_BUTTON(radio), GTK_CHECK_BUTTON(config->group_with));
    }

    gtk_check_button_set_active(GTK_CHECK_BUTTON(radio), config->is_active);
    
    // Layout
    gtk_widget_set_halign(radio, config->halign);
    gtk_widget_set_valign(radio, config->valign);
    gtk_widget_set_margin_top(radio, config->margin_top);
    gtk_widget_set_margin_bottom(radio, config->margin_bottom);

    if (config->on_toggled) {
        g_signal_connect(radio, "toggled", G_CALLBACK(config->on_toggled), config->user_data);
    }

    return radio;
}