#include <gtk/gtk.h>
#include "gui.h"

// Fonction de rappel pour le bouton d'alerte
void on_alert_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(data),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "A new device has been detected!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Fonction principale pour créer la fenêtre de l'interface
void create_gui() {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box;

    gtk_init(NULL, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Network Scanner GUI");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    button = gtk_button_new_with_label("Show Alert");
    g_signal_connect(button, "clicked", G_CALLBACK(on_alert_button_clicked), window);
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
    gtk_main();
}

