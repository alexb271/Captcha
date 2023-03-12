// network includes
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// project includes
#include "mainwindow.h"
#include "../project_server/request_type.h"

ConnectBox connect_box_new() {
    ConnectBox connect_box;

    connect_box.box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_margin_top(connect_box.box, 30);
    gtk_widget_set_margin_bottom(connect_box.box, 30);

    connect_box.connect_label = gtk_label_new(NULL);
    gtk_widget_set_halign(connect_box.connect_label, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(connect_box.connect_label), GTK_JUSTIFY_CENTER);
    gtk_label_set_markup(GTK_LABEL(connect_box.connect_label),
                         "<span weight=\"bold\" size=\"large\">Connect to Server</span>");

    connect_box.address_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_widget_set_halign(connect_box.address_box, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(connect_box.address_box, 30);
    gtk_widget_set_margin_bottom(connect_box.address_box, 30);
    connect_box.ip_addr_entry = gtk_entry_new();
    connect_box.colon_label = gtk_label_new(":");
    connect_box.port_spin_button = gtk_spin_button_new_with_range(0, 65536, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(connect_box.port_spin_button), 9080);
    gtk_editable_set_text(GTK_EDITABLE(connect_box.ip_addr_entry), "127.0.0.1");

    gtk_box_append(GTK_BOX(connect_box.address_box), connect_box.ip_addr_entry);
    gtk_box_append(GTK_BOX(connect_box.address_box), connect_box.colon_label);
    gtk_box_append(GTK_BOX(connect_box.address_box), connect_box.port_spin_button);

    connect_box.format_error_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(connect_box.format_error_label),
                         "<span color=\"red\">Invalid address</span>");
    gtk_widget_set_halign(connect_box.format_error_label, GTK_ALIGN_CENTER);
    gtk_widget_set_visible(connect_box.format_error_label, false);

    connect_box.connection_error_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(connect_box.connection_error_label),
                         "<span color=\"red\">Connection failed</span>");
    gtk_widget_set_halign(connect_box.connection_error_label, GTK_ALIGN_CENTER);
    gtk_widget_set_visible(connect_box.connection_error_label, false);

    connect_box.connect_button = gtk_button_new_with_label("Connect");
    gtk_widget_set_halign(connect_box.connect_button, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(connect_box.box), connect_box.connect_label);
    gtk_box_append(GTK_BOX(connect_box.box), connect_box.address_box);
    gtk_box_append(GTK_BOX(connect_box.box), connect_box.format_error_label);
    gtk_box_append(GTK_BOX(connect_box.box), connect_box.connection_error_label);
    gtk_box_append(GTK_BOX(connect_box.box), connect_box.connect_button);

    return connect_box;
}

CaptchaSelectBox captcha_select_box_new() {
    CaptchaSelectBox captcha_select_box;

    captcha_select_box.box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_margin_top(captcha_select_box.box, 30);
    gtk_widget_set_margin_bottom(captcha_select_box.box, 30);

    captcha_select_box.stat_label = gtk_label_new(NULL);
    gtk_widget_set_halign(captcha_select_box.stat_label, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(captcha_select_box.stat_label), GTK_JUSTIFY_CENTER);

    captcha_select_box.select_label = gtk_label_new(NULL);
    gtk_widget_set_halign(captcha_select_box.select_label, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(captcha_select_box.select_label), GTK_JUSTIFY_CENTER);
    gtk_label_set_markup(GTK_LABEL(captcha_select_box.select_label),
                         "<span weight=\"bold\">Select a captcha</span>");

    captcha_select_box.captcha_button_addition = gtk_button_new_with_label("Addition");
    gtk_widget_set_halign(captcha_select_box.captcha_button_addition, GTK_ALIGN_CENTER);
    captcha_select_box.captcha_button_selection = gtk_button_new_with_label("Selection");
    gtk_widget_set_halign(captcha_select_box.captcha_button_selection, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(captcha_select_box.box), captcha_select_box.stat_label);
    gtk_box_append(GTK_BOX(captcha_select_box.box), captcha_select_box.select_label);
    gtk_box_append(GTK_BOX(captcha_select_box.box), captcha_select_box.captcha_button_addition);
    gtk_box_append(GTK_BOX(captcha_select_box.box), captcha_select_box.captcha_button_selection);

    return captcha_select_box;
}

void captcha_select_box_set_stat_string(CaptchaSelectBox *self, const char *stat_string) {
    gtk_label_set_text(GTK_LABEL(self->stat_label), stat_string);
}

MainWindow main_window_new(GtkApplication *app) {
    MainWindow main_window;

    main_window.window = gtk_application_window_new(app);
    main_window.main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);

    main_window.connect_box = connect_box_new();
    main_window.captcha_select_box = captcha_select_box_new();
    gtk_widget_set_visible(main_window.captcha_select_box.box, false);

    gtk_box_append(GTK_BOX(main_window.main_box), main_window.connect_box.box);
    gtk_box_append(GTK_BOX(main_window.main_box), main_window.captcha_select_box.box);

    gtk_window_set_child(GTK_WINDOW(main_window.window), main_window.main_box);
    gtk_window_set_title(GTK_WINDOW(main_window.window), "Captcha Client");
    gtk_window_set_default_size(GTK_WINDOW(main_window.window), 400, 300);

    return main_window;
}

void main_window_present(const MainWindow *self) {
    gtk_window_present(GTK_WINDOW(self->window));
}

void main_window_on_connect_button_clicked(GtkButton *self, gpointer *user_data) {
    MainWindow *main_window = (MainWindow *)user_data;

    int port = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(
                                                main_window->connect_box.port_spin_button));
    const char* ip_addr_str = gtk_editable_get_text(GTK_EDITABLE(
                                                    main_window->connect_box.ip_addr_entry));
    if (ip_addr_str == NULL || inet_addr(ip_addr_str) == -1) {
        gtk_widget_set_visible(main_window->connect_box.format_error_label, true);
        gtk_widget_set_visible(main_window->connect_box.connection_error_label, false);
        return;
    }
    else {
        main_window->client = captcha_client_new(ip_addr_str, port);
        if (main_window->client.connected) {
            main_window_show_captcha_select(main_window);
        }
        else {
            gtk_widget_set_visible(main_window->connect_box.format_error_label, false);
            gtk_widget_set_visible(main_window->connect_box.connection_error_label, true);
        }
    }
}

void main_window_show_captcha_select(MainWindow *self) {
    gtk_widget_set_visible(self->connect_box.box, false);
    gtk_widget_set_visible(self->captcha_select_box.box, true);

    char message = STATS;
    send(self->client.client_socket, &message, 1, 0);
    char response_buffer[30];
    recv(self->client.client_socket, response_buffer, 30, 0);

    gtk_label_set_text(GTK_LABEL(self->captcha_select_box.stat_label), response_buffer);
}