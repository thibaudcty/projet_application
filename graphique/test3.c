#include <gtk/gtk.h>

void button_clicked(GtkWidget *widget, gpointer window){
	g_print("button clicked \n");
	FILE* demo;
	
     const char * command = " ^C "; 
     int cr = system( command );
     if ( cr != 0 ) {
        fprintf( stderr, 
                 "Impossible de lancer la commande : %s\n",
                 command );
    }
  
     
   }
   

int main(int argc, char **argv){

//-------------lecture du fichier-------------------------
FILE    *textfile;
    char    *text2;
    long    numbytes;
     
    textfile = fopen("texte.txt", "r");
    if(textfile == NULL)
        return 1;
     
    fseek(textfile, 0L, SEEK_END);
    numbytes = ftell(textfile);
    fseek(textfile, 0L, SEEK_SET);  
 
    text2 = (char*)calloc(numbytes, sizeof(char));   
    if(text2 == NULL)
        return 1;
 
    fread(text2, sizeof(char), numbytes, textfile);
    fclose(textfile);
    
//-------------------------------

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

GtkTextBuffer *buffer;
GtkWidget *view;
GtkTextIter start, end;
GtkTextIter iter;

window = gtk_scrolled_window_new(NULL, NULL);
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
 
//------------------partie affichage du résultat du scan--------------
view = gtk_text_view_new();
buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

  gtk_text_buffer_create_tag(buffer, "lmarg", 
      "left_margin", 5, NULL);
  gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, 
        g_strdup_printf("%s\n",text2), -1, "bold", "lmarg",  NULL);

gtk_fixed_put(GTK_FIXED(fixed), view, 80, 170);
//-------------------------------------------------

g_signal_connect(button5, "clicked", G_CALLBACK(button_clicked),NULL);

//-----------------------------------------------
gtk_fixed_put(GTK_FIXED(fixed), button1, 100, 90);
gtk_fixed_put(GTK_FIXED(fixed), button2, 333, 90);
gtk_fixed_put(GTK_FIXED(fixed), label, 140, 20);
gtk_fixed_put(GTK_FIXED(fixed), label2, 80, 60);
gtk_fixed_put(GTK_FIXED(fixed), label3, 80, 150);
gtk_fixed_put(GTK_FIXED(fixed), button3, 100, 350);
gtk_fixed_put(GTK_FIXED(fixed), button4, 333, 350);
gtk_fixed_put(GTK_FIXED(fixed), button5, 450, 480);
//-----------------------------------------------


//gtk_fixed_move(GTK_FIXED(fixed), button1, 200,100);
//gtk_fixed_move(GTK_FIXED(fixed), button2, 350,205);
//gtk_fixed_move(GTK_FIXED(fixed), label, 100,205);

g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); //permet de terminer le programme quand on ferme la fenetre

gtk_container_add(GTK_CONTAINER(window), fixed);
gtk_widget_show_all(window);

gtk_main();


return 0;
}
