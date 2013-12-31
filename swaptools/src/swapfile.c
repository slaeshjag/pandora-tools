#include "swaptools.h"


void swapfile_init() {
	swapfile.entry = NULL;
	swapfile.entries = 0;

	return;
}


void swapfile_clear() {
	int i;

	for (i = 0; i < swapfile.entries; i++)
		free(swapfile.entry[i].path);
	free(swapfile.entry);
	swapfile_init();

	return;
}


int swapfile_new(const char *fname) {
	int i;

	for (i = 0; i < swapfile.entries; i++)
		if (!strcmp(fname, swapfile.entry[i].path))
			return i;

	swapfile.entry = realloc(swapfile.entry, ++swapfile.entries * sizeof(*swapfile.entry));
	swapfile.entry[i].path = strdup(fname);
	swapfile.entry[i].enable_on_boot = swapfile.entry[i].enabled = swapfile.entry[i].size = 0;
	return i;
}


int swapfile_add(const char *fname, int boot_en, int enabled, unsigned long long size) {
	int i;

	i = swapfile_new(fname);
	if (size)
		swapfile.entry[i].size = size;
	if (boot_en)
		swapfile.entry[i].enable_on_boot = 1;
	if (enabled)
		swapfile.entry[i].enabled = 1;
	return i;
}


void swapfile_detect_active() {
	char buff[4096], fname[2048], blah[64];
	unsigned long long size;
	int i;
	FILE *fp;

	if (!(fp = fopen("/proc/swaps", "r")))
		return;

	for (i = 0; !feof(fp); i++) {
		size = 0;
		fgets(buff, 4096, fp);
		if (!i)
			continue;
		if (strchr(buff, '\n'))
			*strchr(buff, '\n') = 0;
		sscanf(buff, "%s %s %llu", fname, blah, &size);
		size >>= 10;
		swapfile_add(fname, 0, 1, size);
	}

	return;
}


void swapfile_detect_boot_enable() {
	char buff[4096], fname[2048], blah[64], type[64], *uuid, *path;
	int i;
	FILE *fp;
	
	if (!(fp = fopen("/etc/fstab", "r")))
		return;
	
	for (i = 0; !feof(fp); i++) {
		fgets(buff, 4096, fp);
		if (*buff == '#')
			continue;
		sscanf(buff, "%s %s %s", fname, blah, type);
		if (strcmp(type, "swap"))
			continue;
		if (strstr(fname, "UUID") == fname) {
			uuid = fname + 5;
			sprintf(buff, "/dev/disk/by-uuid/%s", uuid);
			fname[readlink(buff, fname, 2047)] = 0;
			sprintf(buff, "/dev/disk/by-uuid/%s", fname);
			path = realpath(buff, NULL);
			swapfile_add(path, 1, 0, 0);
			free(path);
		} else {
			swapfile_add(path, 1, 0, 0);
		}
	}

	return;
}


void swapfile_detect() {
	swapfile_detect_active();
	swapfile_detect_boot_enable();

	return;
}
