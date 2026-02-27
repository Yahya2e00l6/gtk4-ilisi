#include "aide.h"

void on_aide_clicked(GtkButton *btn, gpointer parent_window) {
    (void)btn;
    GtkWidget *dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Aide");
    gtk_window_set_default_size(GTK_WINDOW(dialog), 350, 120);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent_window));
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);

    GtkWidget *label = gtk_label_new("Entrez vos informations pour vous inscrire.\n\nVeuillez vérifier que tous les champs sont remplis.");
    gtk_label_set_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_widget_set_margin_top(label, 20);
    gtk_widget_set_margin_bottom(label, 20);
    gtk_widget_set_margin_start(label, 20);
    gtk_widget_set_margin_end(label, 20);

    gtk_window_set_child(GTK_WINDOW(dialog), label);
    gtk_window_present(GTK_WINDOW(dialog));
}