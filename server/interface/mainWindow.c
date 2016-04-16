#include <gtk/gtk.h>

enum
{
	COL_CLIENT = 0,
	NUM_COLS
};


static GtkTreeModel *create_fill_list_clients(void)
{
	GtkListStore *store;
	GtkTreeIter iter;

	store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING);

	//Ajout et remplissage d'une ligne 
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter, COL_CLIENT, "Celine", -1);

	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter, COL_CLIENT, "Emma", -1);
	
	// A supprimer plus tard 
	int i = 0;
	for (i = 0; i < 100; i++)
	{
		gtk_list_store_append (store, &iter);
		gtk_list_store_set (store, &iter, COL_CLIENT, "Kevin", -1);
	}

	return GTK_TREE_MODEL(store); 
}

static GtkWidget *create_view_model (void)
{
	GtkCellRenderer *renderer;
	GtkTreeModel *model;
	GtkWidget *view;

	view = gtk_tree_view_new();

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view), -1, "Client",
						renderer, "text", COL_CLIENT, NULL);

	model = create_fill_list_clients();

	gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);

	g_object_unref(model);

	return view;
}

int main (int argc, char **argv)
{
	GtkWidget *mainWindow;
	GtkWidget *listClients;
	GtkWidget *scrollbar;
	
	gtk_init(&argc, &argv);

	mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(mainWindow), 1000, 500);
	gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(mainWindow), "delete_event", G_CALLBACK(gtk_main_quit), NULL);
	
	listClients = create_view_model();
	scrollbar = gtk_scrolled_window_new(NULL, NULL);
	
	gtk_container_add(GTK_CONTAINER(scrollbar), listClients);
	gtk_container_add(GTK_CONTAINER(mainWindow), scrollbar);
	
	gtk_widget_show_all(mainWindow);

	gtk_main();

	return 0;
}
