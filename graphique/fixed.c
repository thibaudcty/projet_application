#include <gtk/gtk.h>

int main(int argc, char **argv){

gtk_init (&argc, &argv);

//on met le code gtk ici
GtkWidget *window;
GtkWidget *fixed;

GtkWidget *button1;
GtkWidget *button2;
GtkWidget *label;

window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window), "GUI du projet d'application euromed");
gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);


fixed = gtk_fixed_new();
button1 = gtk_button_new_with_label("bouton1");
button2 = gtk_button_new_with_label("bouton2");
label = gtk_label_new("Bienvenue dans notre application :)");

gtk_fixed_put(GTK_FIXED(fixed), button1, 100, 50);
gtk_fixed_put(GTK_FIXED(fixed), button2, 200, 100);
gtk_fixed_put(GTK_FIXED(fixed), label, 120, 20);

gtk_fixed_move(GTK_FIXED(fixed), button1, 200,100);
gtk_fixed_move(GTK_FIXED(fixed), button2, 350,205);
//gtk_fixed_move(GTK_FIXED(fixed), label, 100,205);

g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); //permet de terminer le programme quand on ferme la fenetre

gtk_container_add(GTK_CONTAINER(window), fixed);
gtk_widget_show_all(window);

gtk_main();


return 0;
}
