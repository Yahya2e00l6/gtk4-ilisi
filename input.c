#include "input.h"

GtkWidget *create_input(input_config *config) {
    GtkWidget *entry = gtk_entry_new();

    if (config->placeholder) {
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry), config->placeholder);
    }

    if (config->default_text) {
        gtk_editable_set_text(GTK_EDITABLE(entry), config->default_text);
    }

    if (config->css_class) {
        gtk_widget_add_css_class(entry, config->css_class);
    }

    gtk_entry_set_visibility(GTK_ENTRY(entry), !config->is_password);

    if (config->max_length > 0) {
        gtk_entry_set_max_length(GTK_ENTRY(entry), config->max_length);
    }

    gtk_editable_set_editable(GTK_EDITABLE(entry), config->is_editable);
    gtk_entry_set_input_purpose(GTK_ENTRY(entry), config->purpose);
    gtk_entry_set_alignment(GTK_ENTRY(entry), config->xalign);
    gtk_entry_set_has_frame(GTK_ENTRY(entry), config->has_frame);

    gtk_widget_set_halign(entry, config->halign);
    gtk_widget_set_valign(entry, config->valign);
    gtk_widget_set_hexpand(entry, config->hexpand);

    gtk_widget_set_margin_top(entry, config->margin_top);
    gtk_widget_set_margin_bottom(entry, config->margin_bottom);
    gtk_widget_set_margin_start(entry, config->margin_start);
    gtk_widget_set_margin_end(entry, config->margin_end);

    if (config->on_change) {
        g_signal_connect(entry, "changed", G_CALLBACK(config->on_change), config->user_data);
    }

    if (config->on_activate) {
        g_signal_connect(entry, "activate", G_CALLBACK(config->on_activate), config->user_data);
    }

    return entry;
}

typedef struct {
    void (*on_change)(GtkDropDown *dropdown, gpointer user_data);
    gpointer user_data;
} SelectOnChangeData;

static void select_notify_selected(GObject *gobject, GParamSpec *pspec, gpointer user_data) {
    (void)pspec;

    SelectOnChangeData *data = (SelectOnChangeData *)user_data;
    if (!data || !data->on_change) {
        return;
    }

    data->on_change(GTK_DROP_DOWN(gobject), data->user_data);
}

GtkWidget *create_select(select_config *config) {
    // 1. Create the model (StringList) from your options array
    GtkStringList *string_list = gtk_string_list_new(config->options);
    GtkWidget *dropdown = gtk_drop_down_new(G_LIST_MODEL(string_list), NULL);
    g_object_unref(string_list);

    // 3. Set Default Selection
    if (config->selected_index >= 0) {
        gtk_drop_down_set_selected(GTK_DROP_DOWN(dropdown), (guint)config->selected_index);
    }

    // 4. Layout & Expansion
    gtk_widget_set_halign(dropdown, config->halign);
    gtk_widget_set_valign(dropdown, config->valign);
    gtk_widget_set_hexpand(dropdown, config->hexpand);
    gtk_widget_set_vexpand(dropdown, config->vexpand);
    
    gtk_widget_set_margin_top(dropdown, config->margin_top);
    gtk_widget_set_margin_bottom(dropdown, config->margin_bottom);
    gtk_widget_set_margin_start(dropdown, config->margin_start);
    gtk_widget_set_margin_end(dropdown, config->margin_end);

    // 5. CSS Styling (GTK 4 uses gtk_widget_add_css_class)
    if (config->css_class) {
        gtk_widget_add_css_class(dropdown, config->css_class);
    }

    // 6. Signal Connection
    if (config->on_change) {
        SelectOnChangeData *data = g_new0(SelectOnChangeData, 1);
        data->on_change = config->on_change;
        data->user_data = config->user_data;
        g_signal_connect_data(
            dropdown,
            "notify::selected",
            G_CALLBACK(select_notify_selected),
            data,
            (GClosureNotify)g_free,
            0
        );
    }

    return dropdown;
}

// Updated handler for GTK 4
void my_select_handler(GtkDropDown *dropdown, gpointer user_data) {
    (void)user_data;

    guint selected = gtk_drop_down_get_selected(dropdown);

    // Get the string from the model (works when using GtkStringList)
    GListModel *model = gtk_drop_down_get_model(dropdown);
    const char *selected_text = NULL;
    if (GTK_IS_STRING_LIST(model)) {
        selected_text = gtk_string_list_get_string(GTK_STRING_LIST(model), selected);
    }

    if (selected_text) {
        g_print("User selected index %u: %s\n", selected, selected_text);
    } else {
        g_print("User selected index %u\n", selected);
    }
}


