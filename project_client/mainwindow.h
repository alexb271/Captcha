#pragma once

// gtk includes
#include <gtk/gtk.h>

// project includes
#include "client.h"
#include "connectbox.h"
#include "captchachoosebox.h"
#include "captchaadditionbox.h"
#include "captchaselectionbox.h"
#include "captcharesultbox.h"

typedef struct {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *close_blocked_label;
    ConnectBox connect_box;
    CaptchaChooseBox captcha_choose_box;
    CaptchaAdditionBox captcha_addition_box;
    CaptchaSelectionBox captcha_selection_box;
    CaptchaResultBox captcha_result_box;

    CaptchaClient client;
    bool captcha_in_progress;
} MainWindow;

MainWindow main_window_new(GtkApplication *app);
void main_window_present(const MainWindow *self);
void main_window_show_captcha_choose(MainWindow *self);
void main_window_show_captcha_addition(MainWindow *self);
void main_window_show_captcha_selection(MainWindow *self);
void main_window_show_captcha_result(MainWindow *self);
void main_window_on_connect_button_clicked(GtkButton *self, gpointer *user_data);
void main_window_on_captcha_addition_button_clicked(GtkButton *self, gpointer *user_data);
void main_window_on_captcha_selection_button_clicked(GtkButton *self, gpointer *user_data);
void main_window_on_captcha_addition_submit_button_clicked(GtkButton *self, gpointer *user_data);
void main_window_on_captcha_selection_submit_button_clicked(GtkButton *self, gpointer *user_data);
void main_window_on_captcha_result_back_button_clicked(GtkButton *self, gpointer *user_data);

gboolean main_window_on_close_request(GtkWindow *self, gpointer *user_data);
