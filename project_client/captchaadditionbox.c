#include "captchaadditionbox.h"

CaptchaAdditionBox captcha_addition_box_new() {
    CaptchaAdditionBox captcha_addition_box;
    captcha_addition_box.box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);

    captcha_addition_box.task_label = gtk_label_new(NULL);
    gtk_widget_set_halign(captcha_addition_box.task_label, GTK_ALIGN_CENTER);

    captcha_addition_box.answer_spin_button = gtk_spin_button_new_with_range(0, 65535, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(captcha_addition_box.answer_spin_button), 0);
    gtk_widget_set_halign(captcha_addition_box.answer_spin_button, GTK_ALIGN_CENTER);

    captcha_addition_box.submit_button = gtk_button_new_with_label("Submit");
    gtk_widget_set_halign(captcha_addition_box.submit_button, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(captcha_addition_box.box), captcha_addition_box.task_label);
    gtk_box_append(GTK_BOX(captcha_addition_box.box), captcha_addition_box.answer_spin_button);
    gtk_box_append(GTK_BOX(captcha_addition_box.box), captcha_addition_box.submit_button);

    return captcha_addition_box;
}

void captcha_addition_box_set_task(CaptchaAdditionBox *self, const char *task) {
    gtk_label_set_text(GTK_LABEL(self->task_label), task);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(self->answer_spin_button), 0);
}

