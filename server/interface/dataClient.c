//gcc interface.c -o interface $(pkg-config --libs --cflags gtk+-2.0)
//http://alex.nouvel.free.fr/programmation/C-Gtk/exemple.php?identifiant=5

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

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

/*  box=gtk_vbox_new(FALSE,5);
  gtk_container_add(GTK_CONTAINER(window),box);

  scrollbar = gtk_scrolled_window_new(NULL, NULL);
  gtk_box_pack_start(GTK_BOX(box), scrollbar, TRUE, TRUE, 5);

  text_view=gtk_text_view_new();
  gtk_container_add(GTK_CONTAINER(scrollbar),text_view);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

*/

/*	box = gtk_vbox_new(FALSE, 5);
	gtk_table_attach_defaults(GTK_TABLE(tableCW), box, 3, 7, 0, 3);
	text_view = gtk_text_view_new();
	gtk_box_pack_start(GTK_BOX(box), TRUE, TRUE, 0);


	data.infoClient = gtk_label_new("About the client");
	gtk_table_attach_defaults(GTK_TABLE(tableCW), data.infoClient, 3, 7, 0, 3); */

	// Creation  des boutons
	button[0] = gtk_button_new_with_label("GO BACK");
	gtk_table_attach_defaults(GTK_TABLE(tableCW), button[0], 0, 2, 0, 1);
	g_signal_connect(G_OBJECT(button[0]), "clicked", G_CALLBACK(gtk_main_quit), NULL);

	button[1] = gtk_button_new_with_label("Create client");
	gtk_table_attach_defaults(GTK_TABLE(tableCW), button[1], 0, 1, 2, 3);

	button[2] = gtk_button_new_with_label("Research client");
	gtk_table_attach_defaults(GTK_TABLE(tableCW), button[2], 0, 1, 3, 4);
	//g_signal_connect(G_OBJECT(button[2]), "clicked", G_CALLBACK(test_text), (gpointer) &data);

	button[3] = gtk_button_new_with_label("Update client");
	gtk_table_attach_defaults(GTK_TABLE(tableCW), button[3], 0, 1, 4, 5);

	button[4] = gtk_button_new_with_label("Delete client");
	gtk_table_attach_defaults(GTK_TABLE(tableCW), button[4], 0, 1, 5, 6);

        button[5] = gtk_button_new_with_label("Coucou");
        gtk_table_attach_defaults(GTK_TABLE(tableCW), button[5], 5, 7, 2, 5);
	// Affichage et boucle evenementielle
	gtk_widget_show_all(clientWindow);
	gtk_main();

	return EXIT_SUCCESS;


}
