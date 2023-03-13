#pragma once

// gtk includes
#include <gtk/gtk.h>

#define CAPTCHA_SELECTION_NUMBERS_COUNT 9
typedef struct {
    GtkWidget *box;
    GtkWidget *task_label;
    GtkWidget *toggle_button_box;
    GtkWidget *numbers[CAPTCHA_SELECTION_NUMBERS_COUNT];
    GtkWidget *submit_button;

    char selection_states[CAPTCHA_SELECTION_NUMBERS_COUNT + 1];
} CaptchaSelectionBox;

CaptchaSelectionBox captcha_selection_box_new();
void captcha_selection_box_set_numbers_from_str(CaptchaSelectionBox *self, const char *str);
const char *captcha_selection_box_get_states(CaptchaSelectionBox *self);
