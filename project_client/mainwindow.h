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
    GtkWidget *box;
    GtkWidget *task_label;
    GtkWidget *answer_spin_button;
    GtkWidget *submit_button;
} CaptchaAdditionBox;

CaptchaAdditionBox captcha_addition_box_new();
void captcha_addition_box_set_task(CaptchaAdditionBox *self, const char *task);

typedef struct {
    GtkWidget *box;
    GtkWidget *result_label;
    GtkWidget *back_button;
} CaptchaResultBox;

CaptchaResultBox captcha_result_box_new();
void captcha_result_box_set_result(CaptchaResultBox *self, const char *result);

typedef struct {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *close_blocked_label;
    ConnectBox connect_box;
    CaptchaSelectBox captcha_select_box;
    CaptchaAdditionBox captcha_addition_box;
    CaptchaResultBox captcha_result_box;

    CaptchaClient client;
    bool captcha_in_progress;
} MainWindow;

MainWindow main_window_new(GtkApplication *app);
void main_window_present(const MainWindow *self);
void main_window_show_captcha_select(MainWindow *self);
void main_window_show_captcha_addition(MainWindow *self);
void main_window_show_captcha_result(MainWindow *self);
void main_window_on_connect_button_clicked(GtkButton *self, gpointer *user_data);
void main_window_on_captcha_addition_button_clicked(GtkButton *self, gpointer *user_data);
void main_window_on_captcha_addition_submit_button_clicked(GtkButton *self, gpointer *user_data);
void main_window_on_captcha_result_back_button_clicked(GtkButton *self, gpointer *user_data);

gboolean main_window_on_close_request(GtkWindow *self, gpointer *user_data);
