#pragma once

// gtk includes
#include <gtk/gtk.h>

typedef struct {
    GtkWidget *box;
    GtkWidget *result_label;
    GtkWidget *back_button;
} CaptchaResultBox;

CaptchaResultBox captcha_result_box_new();
void captcha_result_box_set_result(CaptchaResultBox *self, const char *result);
