#pragma once

// gtk includes
#include <gtk/gtk.h>

typedef struct {
    GtkWidget *box;
    GtkWidget *task_label;
    GtkWidget *answer_spin_button;
    GtkWidget *submit_button;
} CaptchaAdditionBox;

CaptchaAdditionBox captcha_addition_box_new();
void captcha_addition_box_set_task(CaptchaAdditionBox *self, const char *task);
