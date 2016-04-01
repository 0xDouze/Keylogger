//gcc $(pkg-config --libs --cflags gtk+-2.0) main.c -o test

#include <stdlib.h>
#include <gtk/gtk.h>


int main(int argc, char **argv)

{

  /* Variables */

  GtkWidget *MainWindow = NULL;
  GtkWidget *Table;
  GtkWidget *Button[2];
  GtkWidget *Text_View;

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
  
  /* Creation d'une table pour positionner les differents widgets */

  Table = gtk_table_new(7, 5, TRUE);
  gtk_container_add(GTK_CONTAINER(MainWindow), GTK_WIDGET(Table));

  // ------------------------------------------------------------------------------------------------
 
  /* Bouton */

  Button[0] = gtk_button_new_from_stock(GTK_STOCK_GO_BACK);
  Button[1] = gtk_button_new_with_label("Bouton");

  gtk_table_attach(GTK_TABLE(Table), Button[0], 0, 1, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0); 
  gtk_table_attach(GTK_TABLE(Table), Button[1], 2, 3, 2, 3, GTK_EXPAND, GTK_EXPAND, 0, 0);

  // ------------------------------------------------------------------------------------------------
  /* Creation de la zone de texte */

  //Text_View = gtk_text_view_new();
  //gtk_box_pack_start(GTK_BOX(main_box), Text_View, TRUE, TRUE, 0);
  // ------------------------------------------------------------------------------------------------

  /* Affichage et boucle évènementielle */

  gtk_widget_show_all(MainWindow);
  //gtk_widget_show(ButtonQuit);
  //g_signal_connect(G_OBJECT(Button[0]), "clicked", G_CALLBACK(gtk_main_quit), NULL); // Quitte lorsque l'utiliqsteur clique sur le bouton
  gtk_main();

  return EXIT_SUCCESS;

}
