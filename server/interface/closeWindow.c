#include <gtk/gtk.h>
#include <stdio.h>

void close_window (GtkWidget *window)
{
	gtk_widget_destroy(window);
}

