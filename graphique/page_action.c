#include <gtk/gtk.h>

void button_clicked(GtkWidget *widget, gpointer data){
	g_print("button clicked \n");
	FILE* demo;
     const char * command = "./page_acceuil"; 
     int cr = system( command );
     const char * command2 = "./^C"; 
     int cr = system( command );
    if ( cr != 0 ) {
        fprintf( stderr, 
                 "Impossible de lancer la commande : %s\n",
                 command );
    }
   }
   

int main(int argc, char **argv){

gtk_init (&argc, &argv);

//on met le code gtk ici
GtkWidget *window;
GtkWidget *fixed;

GtkWidget *button1;
GtkWidget *button2;
GtkWidget *button3;
GtkWidget *button4;
GtkWidget *button5;
GtkWidget *label;
GtkWidget *label2;
GtkWidget *label3;

window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window), "GUI du projet d'application euromed");
gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);


fixed = gtk_fixed_new();
button1 = gtk_button_new_with_label("scan 1: état de la mémoire");
button2 = gtk_button_new_with_label("Scan 2: wazaa");
button3 = gtk_button_new_with_label("stopper la connexion");
button4 = gtk_button_new_with_label("mettre en pause");
button5 = gtk_button_new_with_label("retrour à l'acceuil");
label = gtk_label_new("Gestion du client 2");
label2 = gtk_label_new("Choisir le scan à envoyer :");
label3 = gtk_label_new("Résultat du scan :");

g_signal_connect(button5, "clicked", G_CALLBACK(button_clicked),NULL);

gtk_fixed_put(GTK_FIXED(fixed), button1, 100, 90);
gtk_fixed_put(GTK_FIXED(fixed), button2, 333, 90);
gtk_fixed_put(GTK_FIXED(fixed), label, 140, 20);
gtk_fixed_put(GTK_FIXED(fixed), label2, 80, 60);
gtk_fixed_put(GTK_FIXED(fixed), label3, 80, 150);
gtk_fixed_put(GTK_FIXED(fixed), button3, 100, 350);
gtk_fixed_put(GTK_FIXED(fixed), button4, 333, 350);
gtk_fixed_put(GTK_FIXED(fixed), button5, 450, 480);

//gtk_fixed_move(GTK_FIXED(fixed), button1, 200,100);
//gtk_fixed_move(GTK_FIXED(fixed), button2, 350,205);
//gtk_fixed_move(GTK_FIXED(fixed), label, 100,205);

g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); //permet de terminer le programme quand on ferme la fenetre

gtk_container_add(GTK_CONTAINER(window), fixed);
gtk_widget_show_all(window);

gtk_main();


return 0;
}
