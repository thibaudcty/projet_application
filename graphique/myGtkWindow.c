#include <gtk/gtk.h>

int main(int argc, char **argv){

const char *title;
int width, height; 
gtk_init (&argc, &argv);

//on met le code gtk ici
GtkWidget *window;

window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window), "GUI du projet d'application euromed");
gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);// permet de faire apparaitre la fenetre au centre
gtk_window_set_resizable(GTK_WINDOW(window), FALSE);//true ou false pour faire varier la taille de la fenetre
//gtk_window_maximize(GTK_WINDOW(window));

title = gtk_window_get_title(GTK_WINDOW(window));
printf("your title is: %s\n", title);

gtk_window_get_size(GTK_WINDOW(window), &width, &height);
printf("Width: %d\t Height: %d\n", width, height);


printf("GTK widow decorated ? %d\n", gtk_window_get_decorated(GTK_WINDOW(window)));
printf("GTK widow maximized ? %d\n", gtk_window_is_maximized(GTK_WINDOW(window)));
printf("GTK widow active ? %d\n", gtk_window_is_active(GTK_WINDOW(window)));

g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); //permet de terminer le programme quand on ferme la fenetre

gtk_widget_show_all(window);

gtk_main();


return 0;
}
