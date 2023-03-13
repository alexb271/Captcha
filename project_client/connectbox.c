#include "connectbox.h"

ConnectBox connect_box_new() {
    ConnectBox connect_box;
    connect_box.box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);

    connect_box.connect_label = gtk_label_new(NULL);
    gtk_widget_set_halign(connect_box.connect_label, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(connect_box.connect_label), GTK_JUSTIFY_CENTER);
    gtk_label_set_markup(GTK_LABEL(connect_box.connect_label),
                         "<span weight=\"bold\" size=\"large\">Connect to Server</span>");

    connect_box.address_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_widget_set_halign(connect_box.address_box, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(connect_box.address_box, 30);
    gtk_widget_set_margin_bottom(connect_box.address_box, 30);
    connect_box.ip_addr_entry = gtk_entry_new();
    connect_box.colon_label = gtk_label_new(":");
    connect_box.port_spin_button = gtk_spin_button_new_with_range(0, 65536, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(connect_box.port_spin_button), 9080);
    gtk_editable_set_text(GTK_EDITABLE(connect_box.ip_addr_entry), "127.0.0.1");

    gtk_box_append(GTK_BOX(connect_box.address_box), connect_box.ip_addr_entry);
    gtk_box_append(GTK_BOX(connect_box.address_box), connect_box.colon_label);
    gtk_box_append(GTK_BOX(connect_box.address_box), connect_box.port_spin_button);

    connect_box.format_error_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(connect_box.format_error_label),
                         "<span color=\"red\">Invalid address</span>");
    gtk_widget_set_halign(connect_box.format_error_label, GTK_ALIGN_CENTER);
    gtk_widget_set_visible(connect_box.format_error_label, false);

    connect_box.connection_error_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(connect_box.connection_error_label),
                         "<span color=\"red\">Connection failed</span>");
    gtk_widget_set_halign(connect_box.connection_error_label, GTK_ALIGN_CENTER);
    gtk_widget_set_visible(connect_box.connection_error_label, false);

    connect_box.connect_button = gtk_button_new_with_label("Connect");
    gtk_widget_set_halign(connect_box.connect_button, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(connect_box.box), connect_box.connect_label);
    gtk_box_append(GTK_BOX(connect_box.box), connect_box.address_box);
    gtk_box_append(GTK_BOX(connect_box.box), connect_box.format_error_label);
    gtk_box_append(GTK_BOX(connect_box.box), connect_box.connection_error_label);
    gtk_box_append(GTK_BOX(connect_box.box), connect_box.connect_button);

    return connect_box;
}
