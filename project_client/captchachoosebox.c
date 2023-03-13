#include "captchachoosebox.h"

CaptchaChooseBox captcha_choose_box_new() {
    CaptchaChooseBox captcha_choose_box;
    captcha_choose_box.box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);

    captcha_choose_box.stat_label = gtk_label_new(NULL);
    gtk_widget_set_halign(captcha_choose_box.stat_label, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(captcha_choose_box.stat_label), GTK_JUSTIFY_CENTER);

    captcha_choose_box.select_label = gtk_label_new(NULL);
    gtk_widget_set_halign(captcha_choose_box.select_label, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(captcha_choose_box.select_label), GTK_JUSTIFY_CENTER);
    gtk_label_set_markup(GTK_LABEL(captcha_choose_box.select_label),
                         "<span weight=\"bold\">Select a captcha</span>");

    captcha_choose_box.captcha_button_addition = gtk_button_new_with_label("Addition");
    gtk_widget_set_halign(captcha_choose_box.captcha_button_addition, GTK_ALIGN_CENTER);
    captcha_choose_box.captcha_button_selection = gtk_button_new_with_label("Selection");
    gtk_widget_set_halign(captcha_choose_box.captcha_button_selection, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(captcha_choose_box.box), captcha_choose_box.stat_label);
    gtk_box_append(GTK_BOX(captcha_choose_box.box), captcha_choose_box.select_label);
    gtk_box_append(GTK_BOX(captcha_choose_box.box), captcha_choose_box.captcha_button_addition);
    gtk_box_append(GTK_BOX(captcha_choose_box.box), captcha_choose_box.captcha_button_selection);

    return captcha_choose_box;
}

void captcha_choose_box_set_stat_string(CaptchaChooseBox *self, const char *stat_string) {
    gtk_label_set_text(GTK_LABEL(self->stat_label), stat_string);
}
