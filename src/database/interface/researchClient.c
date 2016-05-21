#include <gtk/gtk.h>
#include <stdio.h>

#include "infoClientWindow.h"

void research_client (GtkWidget *research) //, gpointer data)
{
  // récupération du texte entré par l'utilisateur dans la zone de recherche
  const gchar *client;
  gchar *copy;
  client = gtk_entry_get_text(GTK_ENTRY(research));
  g_print("Donnee entree par l'utilisateur : %s\n", client);
  copy = g_strdup(client);
  infoClientWindow(copy);
  g_free(copy);
}

