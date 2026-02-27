#ifndef SELECT_H
#define SELECT_H
#include <gtk/gtk.h>

typedef struct {
    const char **options; // Must be a NULL-terminated array
    int selected_index;
    const char *css_class;
} select_config;

GtkWidget *create_select(select_config *config);

#endif