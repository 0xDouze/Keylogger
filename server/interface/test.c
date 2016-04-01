#include <gtk/gtk.h>
#include <stdio.h>
 
static GtkWidget *text_view;
 
void saisie(GtkButton *button);
void ouvrir_fichier(GtkWidget *bouton, GtkWidget *file_selection);
 
int main(int argc, char* argv[])
{
  GtkWidget* window;
  GtkWidget* box;
  GtkWidget* button;
  GtkWidget *scrollbar;
  GtkWidget *infoUser;

  gtk_init(&argc, &argv);
                           
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), 480, 480);
  gtk_window_set_title(GTK_WINDOW(window), "XIII. Les zones de texte.");
  g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),0);
                                           
  box=gtk_vbox_new(FALSE,5);
  gtk_container_add(GTK_CONTAINER(window),box);
                                                   
  scrollbar = gtk_scrolled_window_new(NULL, NULL);
  gtk_box_pack_start(GTK_BOX(box), scrollbar, TRUE, TRUE, 5);
                                                           
  text_view=gtk_text_view_new();
  gtk_container_add(GTK_CONTAINER(scrollbar),text_view);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
                                                                       
  button=gtk_button_new_with_label(g_locale_to_utf8( "Sélectionnez un fichier", -1, NULL, NULL, NULL));
  gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);
  g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(saisie),NULL);

  gtk_widget_show_all(window);                                                                                     
  gtk_main();
  return 0;
}
 
 
void saisie(GtkButton *button)
{
      GtkWidget *selection;
           
          selection = gtk_file_selection_new( g_locale_to_utf8( "Sélectionnez un fichier", -1, NULL, NULL, NULL) );
              gtk_widget_show(selection);
                   
                  g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(ouvrir_fichier), selection );
                       
                      g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}
 
void ouvrir_fichier(GtkWidget *bouton, GtkWidget *file_selection)
{
      GtkTextBuffer *buffer;
          GtkTextIter start;
              GtkTextIter end;
                  FILE *fichier;
                      const gchar *chemin;
                          gchar lecture[1024];
                               
                              buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
                                   
                                  chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection));
                                      fichier = fopen(chemin,"rt");
                                           
                                          if(fichier == NULL)
                                                {
                                                          GtkWidget *dialog;
                                                                   
                                                                  dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Impossible d'ouvrir le fichier : \n%s", g_locale_to_utf8(chemin, -1, NULL, NULL, NULL));
                                                                          gtk_dialog_run(GTK_DIALOG(dialog));
                                                                                  gtk_widget_destroy(dialog);
                                                                                          gtk_widget_destroy(file_selection);
                                                                                                   
                                                                                                  return;
                                                                                                      }
                                           
                                              gtk_widget_destroy(file_selection);
                                                   
                                                  gtk_text_buffer_get_start_iter(buffer,&start);
                                                      gtk_text_buffer_get_end_iter(buffer,&end);
                                                          gtk_text_buffer_delete(buffer, &start, &end);
                                                               
                                                              while(fgets(lecture, 1024, fichier))
                                                                    {
                                                                              gtk_text_buffer_get_end_iter(buffer,&end);
                                                                                      gtk_text_buffer_insert(buffer, &end, g_locale_to_utf8(lecture, -1, NULL, NULL, NULL), -1);
                                                                                          }
                                                                   
                                                                  fclose(fichier);
}

