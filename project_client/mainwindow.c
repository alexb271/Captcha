// network includes
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// project includes
#include "mainwindow.h"
#include "../project_server/request_type.h"

MainWindow main_window_new(GtkApplication *app) {
    MainWindow main_window;

    main_window.captcha_in_progress = false;
    main_window.window = gtk_application_window_new(app);
    main_window.main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_margin_top(main_window.main_box, 30);
    gtk_widget_set_margin_bottom(main_window.main_box, 30);
    gtk_widget_set_margin_start(main_window.main_box, 30);
    gtk_widget_set_margin_end(main_window.main_box, 30);

    main_window.close_blocked_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(main_window.close_blocked_label),
                         "<span color=\"red\">Please complete the captcha.</span>");
    gtk_widget_set_halign(main_window.close_blocked_label, GTK_ALIGN_CENTER);
    gtk_widget_set_visible(main_window.close_blocked_label, false);

    main_window.connect_box = connect_box_new();
    main_window.captcha_choose_box = captcha_choose_box_new();
    gtk_widget_set_visible(main_window.captcha_choose_box.box, false);
    main_window.captcha_addition_box = captcha_addition_box_new();
    gtk_widget_set_visible(main_window.captcha_addition_box.box, false);
    main_window.captcha_selection_box = captcha_selection_box_new();
    gtk_widget_set_visible(main_window.captcha_selection_box.box, false);
    main_window.captcha_result_box = captcha_result_box_new();
    gtk_widget_set_visible(main_window.captcha_result_box.box, false);

    gtk_box_append(GTK_BOX(main_window.main_box), main_window.close_blocked_label);
    gtk_box_append(GTK_BOX(main_window.main_box), main_window.connect_box.box);
    gtk_box_append(GTK_BOX(main_window.main_box), main_window.captcha_choose_box.box);
    gtk_box_append(GTK_BOX(main_window.main_box), main_window.captcha_addition_box.box);
    gtk_box_append(GTK_BOX(main_window.main_box), main_window.captcha_selection_box.box);
    gtk_box_append(GTK_BOX(main_window.main_box), main_window.captcha_result_box.box);

    gtk_window_set_child(GTK_WINDOW(main_window.window), main_window.main_box);
    gtk_window_set_title(GTK_WINDOW(main_window.window), "Captcha Client");
    gtk_window_set_default_size(GTK_WINDOW(main_window.window), 400, 300);

    return main_window;
}

void main_window_present(const MainWindow *self) {
    gtk_window_present(GTK_WINDOW(self->window));
}

void main_window_show_captcha_choose(MainWindow *self) {
    gtk_widget_set_visible(self->connect_box.box, false);
    gtk_widget_set_visible(self->captcha_result_box.box, false);
    gtk_widget_set_visible(self->captcha_choose_box.box, true);

    char message = STATS;
    send(self->client.client_socket, &message, 1, 0);
    char response_buffer[30] = { '\0' };
    recv(self->client.client_socket, response_buffer, 30, 0);

    captcha_choose_box_set_stat_string(&(self->captcha_choose_box), response_buffer);
}

void main_window_show_captcha_addition(MainWindow *self) {
    gtk_widget_set_visible(self->captcha_choose_box.box, false);
    gtk_widget_set_visible(self->captcha_addition_box.box, true);
}

void main_window_show_captcha_selection(MainWindow *self) {
    gtk_widget_set_visible(self->captcha_choose_box.box, false);
    gtk_widget_set_visible(self->captcha_selection_box.box, true);
}

void main_window_show_captcha_result(MainWindow *self) {
    gtk_widget_set_visible(self->close_blocked_label, false);
    gtk_widget_set_visible(self->captcha_addition_box.box, false);
    gtk_widget_set_visible(self->captcha_selection_box.box, false);
    gtk_widget_set_visible(self->captcha_result_box.box, true);
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
            main_window_show_captcha_choose(main_window);
        }
        else {
            gtk_widget_set_visible(main_window->connect_box.format_error_label, false);
            gtk_widget_set_visible(main_window->connect_box.connection_error_label, true);
        }
    }
}

void main_window_on_captcha_addition_button_clicked(GtkButton *self, gpointer *user_data) {
    MainWindow *main_window = (MainWindow *)user_data;

    char message = CAPTCHA_MATH;
    send(main_window->client.client_socket, &message, 1, 0);
    char response_buffer[10] = { '\0' };
    recv(main_window->client.client_socket, response_buffer, 10, 0);

    captcha_addition_box_set_task(&(main_window->captcha_addition_box), response_buffer);
    main_window_show_captcha_addition(main_window);
    main_window->captcha_in_progress = true;
}

void main_window_on_captcha_selection_button_clicked(GtkButton *self, gpointer *user_data) {
    MainWindow *main_window = (MainWindow *)user_data;

    char message = CAPTCHA_EVEN_ODD;
    send(main_window->client.client_socket, &message, 1, 0);

    // every number is max 3 characters plus a comma, which is 4.
    char response_buffer[(CAPTCHA_SELECTION_NUMBERS_COUNT * 4) + 1];
    recv(main_window->client.client_socket, response_buffer,
         (CAPTCHA_SELECTION_NUMBERS_COUNT * 4) + 1, 0);

    captcha_selection_box_set_numbers_from_str(&main_window->captcha_selection_box, response_buffer);
    main_window_show_captcha_selection(main_window);
    main_window->captcha_in_progress = true;
}

void main_window_on_captcha_addition_submit_button_clicked(GtkButton *self, gpointer *user_data) {
    MainWindow *main_window = (MainWindow *)user_data;

    uint16_t answer = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(
                                                       main_window->captcha_addition_box.
                                                       answer_spin_button));

    char message[6] = { '\0' };
    sprintf(message, "%d", answer);
    send(main_window->client.client_socket, message, strlen(message), 0);

    char response_buffer[10] = { '\0' };
    recv(main_window->client.client_socket, response_buffer, 10, 0);

    captcha_result_box_set_result(&(main_window->captcha_result_box), response_buffer);
    main_window_show_captcha_result(main_window);
    main_window->captcha_in_progress = false;
}

void main_window_on_captcha_selection_submit_button_clicked(GtkButton *self, gpointer *user_data) {
    MainWindow *main_window = (MainWindow *)user_data;

    const char *response = captcha_selection_box_get_states(&main_window->captcha_selection_box);
    send(main_window->client.client_socket, response, strlen(response), 0);

    char response_buffer[10] = { '\0' };
    recv(main_window->client.client_socket, response_buffer, 10, 0);

    captcha_result_box_set_result(&(main_window->captcha_result_box), response_buffer);
    main_window_show_captcha_result(main_window);
    main_window->captcha_in_progress = false;
}

void main_window_on_captcha_result_back_button_clicked(GtkButton *self, gpointer *user_data) {
    MainWindow *main_window = (MainWindow *)user_data;

    main_window_show_captcha_choose(main_window);
}

gboolean main_window_on_close_request(GtkWindow *self, gpointer *user_data) {
    MainWindow *main_window = (MainWindow *)user_data;

    if (main_window->captcha_in_progress) {
        gtk_widget_set_visible(main_window->close_blocked_label, true);
        return true;
    }

    return false;
}
