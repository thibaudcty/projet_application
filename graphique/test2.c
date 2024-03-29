#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
//--------------------------------------
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

gchar *text = "Résultat du scan : ";
//gchar *text2;
    
  GtkWidget *window;
  GtkWidget *view;
  GtkWidget *vbox;
  
  GtkTextBuffer *buffer;
  GtkTextIter start, end;
  GtkTextIter iter;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
  gtk_window_set_title(GTK_WINDOW(window), "GtkTextView");

  vbox = gtk_box_new(FALSE, 0);
  view = gtk_text_view_scroll_to_mark();
  gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
//---------------------------------------------
  gtk_text_buffer_create_tag(buffer, "gap",
        "pixels_above_lines", 30, NULL);

  gtk_text_buffer_create_tag(buffer, "lmarg", 
      "left_margin", 5, NULL);
  gtk_text_buffer_create_tag(buffer, "blue_fg", 
      "foreground", "blue", NULL); 
  gtk_text_buffer_create_tag(buffer, "gray_bg", 
      "background", "gray", NULL); 
  gtk_text_buffer_create_tag(buffer, "italic", 
      "style", PANGO_STYLE_ITALIC, NULL);
  gtk_text_buffer_create_tag(buffer, "bold", 
      "weight", PANGO_WEIGHT_BOLD, NULL);
//------------------------------------------------

  gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

//--------------------------------------------------
  gtk_text_buffer_insert(buffer, &iter, "Plain text\n", -1);
  gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, 
        "Colored Text\n", -1, "blue_fg", "lmarg",  NULL);
  gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, 
        "Text with colored background\n", -1, "lmarg", "gray_bg", NULL);

  gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, 
        g_strdup_printf("%s\n",text), -1, "italic", "lmarg",  NULL);

  gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, 
        g_strdup_printf("%s\n",text2), -1, "bold", "lmarg",  NULL);
//--------------------------------------------------
  gtk_container_add(GTK_CONTAINER(window), vbox);

//--------------------------------------------------
  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
