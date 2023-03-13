#pragma once

// gtk includes
#include <gtk/gtk.h>

typedef struct {
    GtkWidget *box;
    GtkWidget *stat_label;
    GtkWidget *select_label;
    GtkWidget *captcha_button_addition;
    GtkWidget *captcha_button_selection;
} CaptchaChooseBox;

CaptchaChooseBox captcha_choose_box_new();
void captcha_choose_box_set_stat_string(CaptchaChooseBox *self, const char *stat_string);
