#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <gtk/gtk.h>

typedef struct {
    int column_spacing;
    int row_spacing;
    bool column_homogeneous;
    bool row_homogeneous;
    GtkAlign halign;
    GtkAlign valign;
    bool hexpand;
    bool vexpand;
    int margin_top, margin_bottom, margin_start, margin_end;
} Grid;

typedef struct {
    int column;  // The column number to attach the widget to (starting at 0)
    int row;     // The row number to attach the widget to (starting at 0)
    int width;   // How many columns the widget spans (default 1)
    int height;  // How many rows the widget spans (default 1)
} GridChild;

typedef struct {
    GtkOrientation orientation;
    int spacing;
    bool homogeneous;
    bool hexpand;
    bool vexpand;
    GtkAlign halign;
    GtkAlign valign;
    int margin_top, margin_bottom, margin_start, margin_end;
} Box;

GtkWidget* create_grid(Grid *gridConfig);
GtkWidget* create_box(Box *boxConfig);
void add_to_grid(GtkWidget *grid, GtkWidget *child, GridChild *pos);
#endif