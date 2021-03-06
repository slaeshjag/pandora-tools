#ifndef __SWAPFILE_H__
#define	__SWAPFILE_H__

#include <linux/fs.h>


struct swapfile_entry {
	char			*path;
	int			enable_on_boot;
	int			enabled;
	unsigned long long	size;
};


struct {
	struct swapfile_entry	*entry;
	int			entries;
} swapfile;

int swapfile_get_boot_enabled(const char *fname);
int swapfile_get_enabled(const char *fname);
void swapfile_detect();
void swapfile_init();
void swapfile_clear();


#endif
