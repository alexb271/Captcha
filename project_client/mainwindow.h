#pragma once

// gtk includes
#include <gtk/gtk.h>

// project includes
#include "client.h"

typedef struct {
    GtkWidget *box;
    GtkWidget *connect_label;
    GtkWidget *address_box;
    GtkWidget *ip_addr_entry;
    GtkWidget *colon_label;
    GtkWidget *port_spin_button;
    GtkWidget *format_error_label;
    GtkWidget *connection_error_label;
    GtkWidget *connect_button;
} ConnectBox;

ConnectBox connect_box_new();

typedef struct {
    GtkWidget *box;
    GtkWidget *stat_label;
    GtkWidget *select_label;
    GtkWidget *captcha_button_addition;
    GtkWidget *captcha_button_selection;
} CaptchaSelectBox;

CaptchaSelectBox captcha_select_box_new();
void captcha_select_box_set_stat_string(CaptchaSelectBox *self, const char *stat_string);

typedef struct {
    GtkWidget *window;
    GtkWidget *main_box;
    ConnectBox connect_box;
    CaptchaSelectBox captcha_select_box;

    CaptchaClient client;
} MainWindow;

MainWindow main_window_new(GtkApplication *app);
void main_window_present(const MainWindow *self);
void main_window_on_connect_button_clicked(GtkButton *self, gpointer *user_data);
void main_window_show_captcha_select(MainWindow *self);
