#ifndef __MAIN_WINDOW_H__
#define	__MAIN_WINDOW_H__

struct main_window {
	GtkWidget		*win;
	GtkWidget		*list;

	GtkWidget		*new;
	GtkWidget		*add;
	GtkWidget		*delete;
	GtkWidget		*enable;
	GtkWidget		*boot_enable;
	GtkWidget		*rescan;
};

void mainwindow_init();

#endif
