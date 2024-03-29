#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

void button_clicked(GtkWidget *widget, gpointer data){
	g_print("button clicked \n");
	FILE* demo;
    /*
    // Creates a file "demo_file"
    // with file access as write-plus mode
    demo = fopen("demo_file.txt", "w+");
 
    // adds content to the file
    fprintf(demo, "%s %s %s", "Welcome",
            "to", "le meilleure projet");
 
    // closes the file pointed by demo
    fclose(demo);
    */
     const char * command = "./page_acceuil"; 
    int cr = system( command );
    if ( cr != 0 ) {
        fprintf( stderr, 
                 "Impossible de lancer la commande : %s\n",
                 command );
    }
    
    
 


}

int main(int argc, char **argv){

gtk_init (&argc, &argv);
//lecture de texte

FILE    *textfile;
char    *text;
long    numbytes;

textfile = fopen("texte.txt", "r");
if(textfile == NULL)
return 1;

fseek(textfile, 0L, SEEK_END);
numbytes = ftell(textfile);
fseek(textfile, 0L, SEEK_SET);  

text = (char*)calloc(numbytes, sizeof(char));   
if(text == NULL)
return 1;

fread(text, sizeof(char), numbytes, textfile);
fclose(textfile);


//on met le code gtk ici
GtkWidget *window;
GtkWidget *fixed;

GtkWidget *button1;
GtkWidget *button2;
GtkWidget *label; 
GtkWidget *textview;
GtkTextBuffer *textbuffer;

gchar *text3 = "wazaaaaaa ";
 
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window), "GUI du projet d'application euromed");
gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);


fixed = gtk_fixed_new();
button1 = gtk_button_new_with_label("bouton1");
button2 = gtk_button_new_with_label("bouton2");
label = gtk_label_new("Bienvenue dans notre application :)");
textview = gtk_text_view_new_with_buffer(textbuffer);

g_signal_connect(button2, "clicked", G_CALLBACK(button_clicked),NULL);

gtk_fixed_put(GTK_FIXED(fixed), button1, 100, 50);
gtk_fixed_put(GTK_FIXED(fixed), button2, 200, 100);
gtk_fixed_put(GTK_FIXED(fixed), label, 80, 20);
gtk_fixed_put(GTK_FIXED(fixed), textview, 250, 250);

gtk_fixed_move(GTK_FIXED(fixed), button1, 200,100);
gtk_fixed_move(GTK_FIXED(fixed), button2, 350,205);
//gtk_fixed_move(GTK_FIXED(fixed), label, 100,205);


//--------------text buffer

textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
gtk_text_buffer_set_text(textbuffer, (const gchar *) text, (gint) -1);



g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); //permet de terminer le programme quand on ferme la fenetre

gtk_container_add(GTK_CONTAINER(window), fixed);
gtk_widget_show_all(window);

gtk_main();


return 0;
}
