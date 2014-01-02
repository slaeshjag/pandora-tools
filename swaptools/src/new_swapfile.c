#include "swaptools.h"
#include "new_swapfile.h"


void newswap_spawn() {
	newswapwin.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_modal(GTK_WINDOW(newswapwin.win), TRUE);
	gtk_window_set_title(GTK_WINDOW(newswapwin.win), _("New swap file"));

	gtk_widget_show_all(newswapwin.win);

	return;
}
