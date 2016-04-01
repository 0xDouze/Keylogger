//gcc $(pkg-config --libs --cflags gtk+-2.0) main.c -o test

//http://gtk.developpez.com/cours/gtk2/?page=page_21#LXXI-A-3
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

  /* Creation de la fenetre */

  MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(MainWindow), "Read data");
  const gchar* gtk_window_get_title(GtkWindow *window);
  g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_set_default_size(GTK_WINDOW(MainWindow), 1000, 800);
  gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);


  /* Creation zone de texte */
  
  Text_View = gtk_text_view_new ();
  gtk_box_pack_start(GTK_BOX(MainWindow), Text_View, TRUE, TRUE, 0);

  /* Creation d'un bouton */

  Button[0] = gtk_button_new_from_stock (GTK_STOCK_OPEN);
  gtk_box_pack_start(GTK_BOX(MainWindow), Button[0], FALSE, FALSE, 0);  
  /* Affichage et boucle evenementielle */

  gtk_widget_show_all(MainWindow);
  //g_signal_connect(G_OBJECT(Button[0]), "clicked", G_CALLBACK(cb_open), Text_View);
  gtk_main();

  return EXIT_SUCCESS;

}

