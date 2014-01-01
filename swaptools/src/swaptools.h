#ifndef __SWAPTOOLS_H__
#define	__SWAPTOOLS_H__

#include <libintl.h>
#include <locale.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>

#define	_(STRING)	gettext(STRING)
#include "main_window.h"
#include "swapfile.h"
#include "new_swapfile.h"


struct {
	struct main_window	main_window;
} st;

#endif
