#include "gtk_utils.h"

#include <gtk/gtk.h>
#include <gdk/gdkx.h>

GtkUtils::GtkUtils()
{

}

GtkWidget* gParentView = nullptr;
void* create_browser_window()
{
    GtkWidget* gtkWin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gParentView = gtk_vbox_new(FALSE, 0);
    GtkContainer* container = (GTK_CONTAINER(gtkWin));
    gtk_container_add(container, gParentView);
    gtk_window_set_position(GTK_WINDOW(gtkWin), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(GTK_WIDGET(gtkWin));
    return gParentView;
}

XID getWindowsHandle(void* pWindow)
{
    GdkWindow* w = gtk_widget_get_window((GtkWidget*)pWindow);
    return gdk_x11_drawable_get_xid(w);
}
