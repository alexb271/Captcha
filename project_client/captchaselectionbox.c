#include "captchaselectionbox.h"

CaptchaSelectionBox captcha_selection_box_new() {
    CaptchaSelectionBox captcha_select_box;

    captcha_select_box.box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    captcha_select_box.task_label = gtk_label_new("Select all odd numbers.");
    gtk_widget_set_halign(captcha_select_box.task_label, GTK_ALIGN_CENTER);

    captcha_select_box.toggle_button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_halign(captcha_select_box.toggle_button_box, GTK_ALIGN_CENTER);
    for (size_t i = 0; i < CAPTCHA_SELECTION_NUMBERS_COUNT; i++) {
        captcha_select_box.selection_states[i] = '0';
        captcha_select_box.numbers[i] = gtk_toggle_button_new_with_label("0");
        gtk_box_append(GTK_BOX(captcha_select_box.toggle_button_box), captcha_select_box.numbers[i]);
    }
    captcha_select_box.selection_states[CAPTCHA_SELECTION_NUMBERS_COUNT] = '\0';

    captcha_select_box.submit_button = gtk_button_new_with_label("Submit");
    gtk_widget_set_halign(captcha_select_box.submit_button, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(captcha_select_box.box), captcha_select_box.task_label);
    gtk_box_append(GTK_BOX(captcha_select_box.box), captcha_select_box.toggle_button_box);
    gtk_box_append(GTK_BOX(captcha_select_box.box), captcha_select_box.submit_button);

    return captcha_select_box;
}

void captcha_selection_box_set_numbers_from_str(CaptchaSelectionBox *self, const char *str) {
    size_t idx = 0;
    size_t buf_idx = 0;
    char buffer[4] = { '\0' }; // max 3 decimal digits

    for (size_t i = 0; i < CAPTCHA_SELECTION_NUMBERS_COUNT; i++) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self->numbers[i]), false);
        self->selection_states[i] = '0';

        while (str[idx] != ',') {
            if (str[idx] == '\0') { return; }

            buffer[buf_idx] = str[idx];
            idx += 1;
            if (buf_idx < 3) {
                buf_idx += 1;
            }
            else {
                gtk_button_set_label(GTK_BUTTON(self->numbers[i]), buffer);
                for (size_t j = 0; j < 4; j++) { buffer[j] = '\0'; }
                buf_idx = 0;
            }
        }
        idx += 1;
        gtk_button_set_label(GTK_BUTTON(self->numbers[i]), buffer);
        for (size_t j = 0; j < 4; j++) { buffer[j] = '\0'; }
        buf_idx = 0;
    }
}

const char *captcha_selection_box_get_states(CaptchaSelectionBox *self) {
    for (size_t i = 0; i < CAPTCHA_SELECTION_NUMBERS_COUNT; i++) {
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self->numbers[i]))) {
            self->selection_states[i] = '1';
        }
    }
    return self->selection_states;
}
