#include <gtk/gtk.h>
#include <stdlib.h>

#include "closeWindow.h"
#include "infoClientWindow.h"
#include "researchClient.h"

void view_popup_menu_onDoSomething ();

void view_popup_menu (GtkWidget *treeview, GdkEventButton *event, gchar *data);

gboolean view_onButtonPressed (GtkWidget *treeview, GdkEventButton *event);

gboolean view_onPopupMenu (GtkWidget *treeview, gchar *data);
//static 

GtkTreeModel *create_fill_list_clients(void);
//static 

GtkWidget *create_view_model (void);

void *mainWindow (void* arg);

