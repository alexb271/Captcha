// gtk includes
#include <gtk/gtk.h>

// project includes
#include "mainwindow.h"

static void on_activate(GtkApplication *app, gpointer *user_data) {
    MainWindow **main_window = (MainWindow **)user_data;
    *main_window = main_window_new(app);
    main_window_present(*main_window);
}

int main(int argc, char **argv) {
    MainWindow *main_window;
    GtkApplication *app = gtk_application_new("com.captcha.client", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), &main_window);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    g_free(main_window);
    return status;
}
