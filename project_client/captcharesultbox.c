#include "captcharesultbox.h"

CaptchaResultBox captcha_result_box_new() {
    CaptchaResultBox captcha_result_box;
    captcha_result_box.box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);

    captcha_result_box.result_label = gtk_label_new(NULL);
    captcha_result_box.back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(captcha_result_box.result_label, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(captcha_result_box.back_button, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(captcha_result_box.box), captcha_result_box.result_label);
    gtk_box_append(GTK_BOX(captcha_result_box.box), captcha_result_box.back_button);

    return captcha_result_box;
}

void captcha_result_box_set_result(CaptchaResultBox *self, const char *result) {
    gtk_label_set_text(GTK_LABEL(self->result_label), result);
}
