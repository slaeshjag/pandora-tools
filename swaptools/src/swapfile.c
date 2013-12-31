#include "swaptools.h"


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
		size /= 1024;
		fprintf(stderr, "%s (size: %llu MB) active\n", fname, size);
	}

	return;
}
