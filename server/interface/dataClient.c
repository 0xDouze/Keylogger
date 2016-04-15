//gcc interface.c -o interface $(pkg-config --libs --cflags gtk+-2.0)
//http://alex.nouvel.free.fr/programmation/C-Gtk/exemple.php?identifiant=5
//http://scentric.net/tutorial/ch-treeview.html

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

//#include "menuBar.h"

/*void test_text ()
{
	gchar *test;
	sprintf(test,"Coucou");
	gtk_label_set_text(GTK_LABEL(data->labelResultat), test);
}*/

int main(int argc, char **argv)
{
	// Variables
	GtkWidget *clientWindow;
	GtkWidget *tableCW;
	GtkWidget *button[5];
//	GtkWidget *infoClient;
//	GtkWidget *box;
//	Data data;

	// Initialisation de GTK
	gtk_init(&argc, &argv);

	// Creation de la fenetre principale
	clientWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(clientWindow), "Server");
	gtk_window_set_default_size(GTK_WINDOW(clientWindow), 1000, 700);
	gtk_window_set_position(GTK_WINDOW(clientWindow), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(clientWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

	// Creation de la table
	tableCW = gtk_table_new(10, 7, TRUE);
	gtk_container_add(GTK_CONTAINER(clientWindow), GTK_WIDGET(tableCW));

	//Creation de la barre de menu
  GtkWidget *menuBar;
  menuBar = gtk_menu_bar_new();

        	//Menu "File"
  GtkWidget *menu;
  GtkWidget *menuItem;

  menu = gtk_menu_new();
  menuItem = gtk_menu_item_new_with_mnemonic("_Quitter");
	gtk_widget_show(menuItem);
  g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(gtk_main_quit), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);
	gtk_widget_show(menuBar);
	menuItem = gtk_menu_item_new_with_mnemonic("_File");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);
        	//Sous-menu File
        /*GtkWidget *submenuItem;

        submenuItem = gtk_menu_item_new_with_mnemonic("_Quit");
        gtk_menu_shell_append(GTK_MENU_SHELL(menuItem), submenuItem);
	g_signal_connect(G_OBJECT(submenuItem), "activate", G_CALLBACK(gtk_main_quit), NULL);  
	*/
        //gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);
        //gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);

	gtk_table_attach_defaults(GTK_TABLE(tableCW), menuBar, 0, 10, 0, 1);

	// Creation  des boutons
	button[0] = gtk_button_new_with_label("GO BACK");
	gtk_table_attach_defaults(GTK_TABLE(tableCW), button[0], 0, 2, 1, 2);
	g_signal_connect(G_OBJECT(button[0]), "clicked", G_CALLBACK(gtk_main_quit), NULL);

	button[1] = gtk_button_new_with_label("Create client");
	gtk_table_attach_defaults(GTK_TABLE(tableCW), button[1], 1, 2, 2, 3);

	button[2] = gtk_button_new_with_label("Research client");
	gtk_table_attach_defaults(GTK_TABLE(tableCW), button[2], 1, 2, 3, 4);
	//g_signal_connect(G_OBJECT(button[2]), "clicked", G_CALLBACK(test_text), (gpointer) &data);

	button[3] = gtk_button_new_with_label("Update client");
	gtk_table_attach_defaults(GTK_TABLE(tableCW), button[3], 1, 2, 4, 5);

	button[4] = gtk_button_new_with_label("Delete client");
	gtk_table_attach_defaults(GTK_TABLE(tableCW), button[4], 1, 2, 5, 6);

	// Affichage et boucle evenementielle
	gtk_widget_show(menuBar);
	gtk_widget_show_all(clientWindow);
	gtk_main();

	return EXIT_SUCCESS;


}
