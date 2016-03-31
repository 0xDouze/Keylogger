//gcc $(pkg-config --libs --cflags gtk+-2.0) main.c -o test

#include <stdlib.h>
#include <gtk/gtk.h>


int main(int argc, char **argv)

{

  /* Variables */

  GtkWidget * MainWindow = NULL;


  /* Initialisation de GTK+ */

  gtk_init(&argc, &argv);

  // ------------------------------------------------------------------------------------------------

  /* Création de la fenêtre */

  MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(MainWindow), "Server");
  const gchar* gtk_window_get_title(GtkWindow *window);
  g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  
  //gint width = 500;
  //gint height = 500;
  gtk_window_set_default_size(GTK_WINDOW(MainWindow), 1000, 800); // taille de la fenetre par defaut
  void gtk_window_get_default_size (GtkWindow *window, gint *width, gint *height);

  void gtk_window_resize (GtkWindow *window, gint width, gint height); // taille actuelle de la fenetre
  void gtk_window_get_size (GtkWindow *window, gint *width, gint *height);

  gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER); // centrage de la fenetre

  // ------------------------------------------------------------------------------------------------

  /* Bouton */

  GtkWidget *ButtonQuit;

  ButtonQuit = gtk_button_new_with_label("Quitter");
  gtk_window_set_title(GTK_WINDOW(MainWindow), "Les boutons - Exemple 1");
  
  //GtkWidget* gtk_button_new_with_label(const gchar *label); // initialisation du bouton

  // ------------------------------------------------------------------------------------------------

  /* Affichage et boucle évènementielle */

  gtk_widget_show(MainWindow);
  g_signal_connect(G_OBJECT(ButtonQuit), "clicked", G_CALLBACK(gtk_main_quit), NULL); // Quitte lorsque l4utiliqsteur clique sur le bouton
  gtk_main();

  return EXIT_SUCCESS;

}
