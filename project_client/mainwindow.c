// project includes
#include "mainwindow.h"
#include "../project_server/request_type.h"

MainWindow *main_window_new(GtkApplication *app) {
    MainWindow *main_window = g_malloc(sizeof(MainWindow));

    main_window->captcha_in_progress = false;
    main_window->window = gtk_application_window_new(app);
    main_window->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_margin_top(main_window->main_box, 30);
    gtk_widget_set_margin_bottom(main_window->main_box, 30);
    gtk_widget_set_margin_start(main_window->main_box, 30);
    gtk_widget_set_margin_end(main_window->main_box, 30);

    main_window->close_blocked_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(main_window->close_blocked_label),
                         "<span color=\"red\">Please complete the captcha.</span>");
    gtk_widget_set_halign(main_window->close_blocked_label, GTK_ALIGN_CENTER);
    gtk_widget_set_visible(main_window->close_blocked_label, false);

    main_window->connect_box = connect_box_new();
    main_window->captcha_choose_box = captcha_choose_box_new();
    gtk_widget_set_visible(main_window->captcha_choose_box.box, false);
    main_window->captcha_addition_box = captcha_addition_box_new();
    gtk_widget_set_visible(main_window->captcha_addition_box.box, false);
    main_window->captcha_selection_box = captcha_selection_box_new();
    gtk_widget_set_visible(main_window->captcha_selection_box.box, false);
    main_window->captcha_result_box = captcha_result_box_new();
    gtk_widget_set_visible(main_window->captcha_result_box.box, false);

    gtk_box_append(GTK_BOX(main_window->main_box), main_window->close_blocked_label);
    gtk_box_append(GTK_BOX(main_window->main_box), main_window->connect_box.box);
    gtk_box_append(GTK_BOX(main_window->main_box), main_window->captcha_choose_box.box);
    gtk_box_append(GTK_BOX(main_window->main_box), main_window->captcha_addition_box.box);
    gtk_box_append(GTK_BOX(main_window->main_box), main_window->captcha_selection_box.box);
    gtk_box_append(GTK_BOX(main_window->main_box), main_window->captcha_result_box.box);

    gtk_window_set_child(GTK_WINDOW(main_window->window), main_window->main_box);
    gtk_window_set_title(GTK_WINDOW(main_window->window), "Captcha Client");
    gtk_window_set_default_size(GTK_WINDOW(main_window->window), 400, 300);

    g_signal_connect(main_window->connect_box.connect_button, "clicked",
                     G_CALLBACK(main_window_on_connect_button_clicked), main_window);
    g_signal_connect(main_window->captcha_choose_box.captcha_button_addition, "clicked",
                     G_CALLBACK(main_window_on_captcha_addition_button_clicked), main_window);
    g_signal_connect(main_window->captcha_choose_box.captcha_button_selection, "clicked",
                     G_CALLBACK(main_window_on_captcha_selection_button_clicked), main_window);
    g_signal_connect(main_window->captcha_addition_box.submit_button, "clicked",
                     G_CALLBACK(main_window_on_captcha_addition_submit_button_clicked), main_window);
    g_signal_connect(main_window->captcha_selection_box.submit_button, "clicked",
                     G_CALLBACK(main_window_on_captcha_selection_submit_button_clicked), main_window);
    g_signal_connect(main_window->captcha_result_box.back_button, "clicked",
                     G_CALLBACK(main_window_on_captcha_result_back_button_clicked), main_window);
    g_signal_connect(main_window->window, "close-request",
                     G_CALLBACK(main_window_on_close_request), main_window);

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
    captcha_client_send(&self->client, &message, 1);
    char response_buffer[30] = { '\0' };
    captcha_client_receive(&self->client, response_buffer, 30);

    captcha_choose_box_set_stat_string(&self->captcha_choose_box, response_buffer);
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

void main_window_on_connect_button_clicked(GtkButton *button, gpointer *user_data) {
    MainWindow *self = (MainWindow *)user_data;

    int port = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(
                                                self->connect_box.port_spin_button));
    const char* ip_addr_str = gtk_editable_get_text(GTK_EDITABLE(
                                                    self->connect_box.ip_addr_entry));
    if (ip_addr_str == NULL || inet_addr(ip_addr_str) == -1) {
        gtk_widget_set_visible(self->connect_box.format_error_label, true);
        gtk_widget_set_visible(self->connect_box.connection_error_label, false);
        return;
    }
    else {
        self->client = captcha_client_new(ip_addr_str, port);
        if (self->client.connected) {
            main_window_show_captcha_choose(self);
        }
        else {
            gtk_widget_set_visible(self->connect_box.format_error_label, false);
            gtk_widget_set_visible(self->connect_box.connection_error_label, true);
        }
    }
}

void main_window_on_captcha_addition_button_clicked(GtkButton *button, gpointer *user_data) {
    MainWindow *self = (MainWindow *)user_data;

    char message = CAPTCHA_MATH;
    captcha_client_send(&self->client, &message, 1);
    char response_buffer[10] = { '\0' };
    captcha_client_receive(&self->client, response_buffer, 10);

    captcha_addition_box_set_task(&self->captcha_addition_box, response_buffer);
    main_window_show_captcha_addition(self);
    self->captcha_in_progress = true;
}

void main_window_on_captcha_selection_button_clicked(GtkButton *button, gpointer *user_data) {
    MainWindow *self = (MainWindow *)user_data;

    char message = CAPTCHA_EVEN_ODD;
    captcha_client_send(&self->client, &message, 1);

    // every number is max 3 characters plus a comma, which is 4.
    char response_buffer[(CAPTCHA_SELECTION_NUMBERS_COUNT * 4) + 1];
    captcha_client_receive(&self->client, response_buffer,
                           (CAPTCHA_SELECTION_NUMBERS_COUNT * 4) + 1);

    captcha_selection_box_set_numbers_from_str(&self->captcha_selection_box, response_buffer);
    main_window_show_captcha_selection(self);
    self->captcha_in_progress = true;
}

void main_window_on_captcha_addition_submit_button_clicked(GtkButton *button, gpointer *user_data) {
    MainWindow *self = (MainWindow *)user_data;

    uint16_t answer = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(
                                                       self->captcha_addition_box.
                                                       answer_spin_button));

    char message[6] = { '\0' };
    sprintf(message, "%d", answer);
    captcha_client_send(&self->client, message, strlen(message));

    char response_buffer[10] = { '\0' };
    captcha_client_receive(&self->client, response_buffer, 10);

    captcha_result_box_set_result(&self->captcha_result_box, response_buffer);
    main_window_show_captcha_result(self);
    self->captcha_in_progress = false;
}

void main_window_on_captcha_selection_submit_button_clicked(GtkButton *button, gpointer *user_data) {
    MainWindow *self = (MainWindow *)user_data;

    const char *response = captcha_selection_box_get_states(&self->captcha_selection_box);
    captcha_client_send(&self->client, response, strlen(response));

    char response_buffer[10] = { '\0' };
    recv(self->client.client_socket, response_buffer, 10, 0);

    captcha_result_box_set_result(&self->captcha_result_box, response_buffer);
    main_window_show_captcha_result(self);
    self->captcha_in_progress = false;
}

void main_window_on_captcha_result_back_button_clicked(GtkButton *button, gpointer *user_data) {
    MainWindow *self = (MainWindow *)user_data;

    main_window_show_captcha_choose(self);
}

gboolean main_window_on_close_request(GtkWindow *window, gpointer *user_data) {
    MainWindow *self = (MainWindow *)user_data;

    if (self->captcha_in_progress) {
        gtk_widget_set_visible(self->close_blocked_label, true);
        return true; // request handled
    }

    captcha_client_disconnect(&self->client);
    return false; // request will be propagated to further handlers
}
