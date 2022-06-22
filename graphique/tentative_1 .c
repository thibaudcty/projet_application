#include <gtk/gtk.h>
#include <ctype.h>


GtkWidget *window;
GtkWidget *fixed;
GtkWidget *button1;
GtkWidget *button2;
GtkWidget *label;

int main(int argc, char **argv){

gtk_init (&argc, &argv);

//on met le code gtk ici

builder = gtk_builer_new_from_file ("tentative_1.glade");

window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));


fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));


g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); //permet de terminer le programme quand on ferme la fenetre

gtk_builder_connect_signals(builder, NULL);
gtk_container_add(GTK_CONTAINER(window), fixed);
gtk_widget_show(window);
}
gtk_main();


