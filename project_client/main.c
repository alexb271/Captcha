// gtk includes
#include <gtk/gtk.h>

// project includes
#include "client.h"
#include "mainwindow.h"

static void on_activate(GtkApplication *app, gpointer *user_data) {
    MainWindow *main_window = (MainWindow *)user_data;
    *main_window = main_window_new(app);
    g_signal_connect(main_window->connect_box.connect_button, "clicked",
                     G_CALLBACK(main_window_on_connect_button_clicked), main_window);

    main_window_present(main_window);
}

int main(int argc, char **argv) {
    MainWindow main_window;

    GtkApplication *app = gtk_application_new("com.captcha.client", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), &main_window);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    captcha_client_disconnect(&main_window.client);
    return status;
}
