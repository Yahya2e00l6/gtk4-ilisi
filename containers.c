#include "containers.h"

GtkWidget* create_grid(Grid *config) {
    GtkWidget *grid = gtk_grid_new();

    gtk_grid_set_column_spacing(GTK_GRID(grid), config->column_spacing);
    gtk_grid_set_row_spacing(GTK_GRID(grid), config->row_spacing);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), config->column_homogeneous);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), config->row_homogeneous);

    gtk_widget_set_halign(grid, config->halign);
    gtk_widget_set_valign(grid, config->valign);
    gtk_widget_set_hexpand(grid, config->hexpand);
    gtk_widget_set_vexpand(grid, config->vexpand);

    gtk_widget_set_margin_top(grid, config->margin_top);
    gtk_widget_set_margin_bottom(grid, config->margin_bottom);
    gtk_widget_set_margin_end(grid, config->margin_end);
    gtk_widget_set_margin_start(grid, config->margin_start);

    return grid;
}

void add_to_grid(GtkWidget *grid, GtkWidget *child, GridChild *pos) {
    gtk_grid_attach(GTK_GRID(grid), child, pos->column, pos->row, pos->width, pos->height);
}

GtkWidget* create_box(Box *boxConfig) {
    GtkWidget *box = gtk_box_new(boxConfig->orientation, boxConfig->spacing);
    gtk_box_set_homogeneous(GTK_BOX(box), boxConfig->homogeneous);
    
    gtk_widget_set_margin_top(box, boxConfig->margin_top);
    gtk_widget_set_margin_bottom(box, boxConfig->margin_bottom);
    gtk_widget_set_margin_start(box, boxConfig->margin_start);
    gtk_widget_set_margin_end(box, boxConfig->margin_end);
    gtk_widget_set_halign(box, boxConfig->halign);
    gtk_widget_set_valign(box, boxConfig->valign);
    gtk_widget_set_hexpand(box, boxConfig->hexpand);
    gtk_widget_set_vexpand(box, boxConfig->vexpand);
    
    return box;
}