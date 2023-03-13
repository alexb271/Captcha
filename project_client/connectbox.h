#pragma once

// gtk includes
#include <gtk/gtk.h>

typedef struct {
    GtkWidget *box;
    GtkWidget *connect_label;
    GtkWidget *address_box;
    GtkWidget *ip_addr_entry;
    GtkWidget *colon_label;
    GtkWidget *port_spin_button;
    GtkWidget *format_error_label;
    GtkWidget *connection_error_label;
    GtkWidget *connect_button;
} ConnectBox;

ConnectBox connect_box_new();
