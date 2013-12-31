#include "swaptools.h"
#define	__DEBUG


void init_locale() {
	setlocale(LC_ALL, "");
	#ifdef __DEBUG
	bindtextdomain("swaptools", "build/share/locale");
	#endif

	textdomain("swaptools");
	
	return;
}


int main(int argc, char **argv) {
	init_locale();
	gtk_init(&argc, &argv);

	mainwindow_init();

	gtk_main();

	return 0;
}
