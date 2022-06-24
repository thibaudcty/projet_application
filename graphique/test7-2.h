#include <gtk/gtk.h>

void cb_create_entry(GtkWidget *p_widget, gpointer user_data){
    gtk_button_released(p_widget);
    GtkWidget *p_window;
    GtkWidget *p_v_box;
    GtkWidget *p_entry;

GtkWidget *fixed;
GtkWidget *button1;
GtkWidget *button2;
GtkWidget *button3;
GtkWidget *button4;
GtkWidget *button5;
GtkWidget *button6;
GtkWidget *label;
GtkWidget *label2;
GtkWidget *label3;

fixed = gtk_fixed_new();
    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(p_window), "GUI du projet d'application euromed");
gtk_window_set_default_size(GTK_WINDOW(p_window), 500, 500);

gtk_fixed_put(GTK_FIXED(fixed), button1, 125, 90);
gtk_fixed_put(GTK_FIXED(fixed), button2, 250, 90);
gtk_fixed_put(GTK_FIXED(fixed), button6, 375, 90);
gtk_fixed_put(GTK_FIXED(fixed), label, 140, 20);
gtk_fixed_put(GTK_FIXED(fixed), label2, 80, 60);
gtk_fixed_put(GTK_FIXED(fixed), label3, 80, 150);
gtk_fixed_put(GTK_FIXED(fixed), button3, 100, 350);
gtk_fixed_put(GTK_FIXED(fixed), button4, 333, 350);
gtk_fixed_put(GTK_FIXED(fixed), button5, 450, 480);


    p_v_box = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(p_window), p_v_box);

    
   gtk_container_add(GTK_CONTAINER(p_window), fixed);
    gtk_widget_show_all(p_window);
}
