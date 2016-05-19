#include <gtk/gtk.h>
#include <stdio.h>

#include "closeWindow.h"

void infoClientWindow (gchar *data)
{

  GtkWidget *infoWindow;
  GtkWidget *boxH;
  GtkWidget *boxV;
  GtkWidget *btnDeleteClient;
  GtkWidget *btnGoBack;
  GtkWidget *btnUpdateClient;
  GtkWidget *pLabel;
  GtkWidget *scrollbar;

  // Creation de la fenetre principale
  infoWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(infoWindow), 1000, 700);
  gtk_window_set_position(GTK_WINDOW(infoWindow), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(infoWindow), data);

  boxV = gtk_vbox_new(FALSE, 0);
  boxH = gtk_hbox_new(TRUE, 0);

  scrollbar = gtk_scrolled_window_new(NULL, NULL);
  
  // Temporaire
  pLabel = gtk_label_new("Hello world erezrze zer zr zer zer zer zer zr zer zer rezrzerze ezr dddgdd gdffdfd d gfdfgfdd dfgdfgdf ggg g g g g g dgdfgdfg dgf test");

  //Creation des boutons
  btnDeleteClient = gtk_button_new_with_label("Delete client");
  btnGoBack = gtk_button_new_with_label("Go back");
  btnUpdateClient = gtk_button_new_with_label("Update client");  

  // Insertion des widgets
  gtk_container_add(GTK_CONTAINER(infoWindow), boxV);
  gtk_container_add(GTK_CONTAINER(scrollbar), pLabel);

  gtk_box_pack_start(GTK_BOX(boxV), scrollbar, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(boxV), boxH, FALSE, TRUE, 20); 
 
  gtk_box_pack_start(GTK_BOX(boxH), btnGoBack, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(boxH), btnDeleteClient, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(boxH), btnUpdateClient, FALSE, FALSE, 0);

  // Detection des click
  g_signal_connect_swapped(G_OBJECT(infoWindow), "delete-event", G_CALLBACK(close_window), infoWindow);
  g_signal_connect_swapped(G_OBJECT(btnGoBack), "clicked", G_CALLBACK(close_window), infoWindow);
  
  gtk_widget_show_all(infoWindow);
  //gtk_main();

}
