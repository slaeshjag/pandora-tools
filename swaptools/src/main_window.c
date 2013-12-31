#include "swaptools.h"

void mainwindow_list_add_entry(GtkWidget *list, const char *location, int size, int enabled, int boot_en);
void mainwindow_populate_list(GtkWidget *list);

void mainwindow_add_custom(GtkWidget *menu_item, gpointer data) {
	fprintf(stderr, "Add custom!\n");
}



void mainwindow_init_list(GtkWidget *list) {
	GtkCellRenderer *renderer, *icon_rend, *icon_rend2;
	GtkTreeViewColumn *location, *size, *enabled, *boot_en;
	GtkListStore *store;

	renderer = gtk_cell_renderer_text_new();
	icon_rend = gtk_cell_renderer_pixbuf_new();
	icon_rend2 = gtk_cell_renderer_pixbuf_new();
	location = gtk_tree_view_column_new_with_attributes(_("Location"), renderer, "text", 0, NULL);
	gtk_tree_view_column_set_expand(location, TRUE);
	size = gtk_tree_view_column_new_with_attributes(_("Size"), renderer, "text", 3, NULL);
	enabled = gtk_tree_view_column_new_with_attributes(_("Enabled"), icon_rend, "icon-name", 1, NULL);
	boot_en = gtk_tree_view_column_new_with_attributes(_("Enabled at boot"), icon_rend2, "icon-name", 2, NULL);
	store = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), location);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), enabled);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), boot_en);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), size);
	g_object_unref(store);

	return;
}


void mainwindow_init() {
	GtkWidget *vbox, *menubar, *file, *filemenu, *custom, *quit;
	GtkWidget *list;

	st.main_window.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* Main window */
	gtk_window_set_title(GTK_WINDOW(st.main_window.win), _("Swap files"));
	gtk_window_set_default_size(GTK_WINDOW(st.main_window.win), 700, 400);
	gtk_window_set_position(GTK_WINDOW(st.main_window.win), GTK_WIN_POS_CENTER);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(st.main_window.win), vbox);
	menubar = gtk_menu_bar_new();
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

	/* Create file menu */
	filemenu = gtk_menu_new();
	file = gtk_menu_item_new_with_label(_("File"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

	custom = gtk_image_menu_item_new_with_label(_("Add existing swap file..."));
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(custom), gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU));
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), custom);
	g_signal_connect(G_OBJECT(custom), "activate", G_CALLBACK(mainwindow_add_custom), NULL);

	quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
	g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);



	/* Create main listbox */
	list = gtk_tree_view_new();
	mainwindow_init_list(list);
	gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);
	
	swapfile_detect();
	mainwindow_populate_list(list);

	g_signal_connect_swapped(G_OBJECT(st.main_window.win), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(st.main_window.win);

	return;
}


void mainwindow_list_add_entry(GtkWidget *list, const char *location, int size, int enabled, int boot_en) {
	GtkListStore *store;
	GtkTreeIter iter;
	char buff[32];

	sprintf(buff, "%'i %s", size, _("Megabytes"));

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, location, 1, "gtk-yes", 2, "gtk-no", 3, buff, -1);
	gtk_list_store_set(store, &iter, 1, enabled ? "gtk-yes" : "gtk-no", 2, boot_en ? "gtk-yes" : "gtk-no", -1);

	return;
}


void mainwindow_populate_list(GtkWidget *list) {
	int i;

	for (i = 0; i < swapfile.entries; i++)
		mainwindow_list_add_entry(list, swapfile.entry[i].path, swapfile.entry[i].size, swapfile.entry[i].enabled, swapfile.entry[i].enable_on_boot);
	return;
}
