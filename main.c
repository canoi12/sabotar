#include "sabotar.h"

#include <stdio.h>
#include <string.h>

void print_posix(posix_header_t h) {
	printf("| %s |", h.name);
	printf(" %.8s |", h.mode);
	printf(" %.8s |", h.uid);
	printf(" %.8s |", h.gid);
	printf(" %.12s |", h.size);
	printf(" %.12s |", h.mtime);
	printf(" %.8s |", h.chksum);
	printf(" %c |", h.typeflag);
	printf(" %s |", h.linkname);
	printf(" %.6s |", h.magic);
	printf(" %.2s |", h.version);
	printf(" %s |", h.uname);
	printf(" %s |", h.gname);
	printf(" %.8s |", h.devmajor);
	printf(" %.8s |", h.devminor);
	printf(" %s |", h.prefix);

	printf("\n");
}

int calc_checksum(posix_header_t h) {
	int sum = 0;
	int i;
	char* bytes = (char*)&h;
	for (i = 0; i < 7; i++) {
		/* printf("%c ", p.chksum[i]); */
		h.chksum[i] = ' ';
	}
	for (i = 0; i < SBTAR_BLOCK_SIZE; i++) {
		sum += bytes[i];
	}
	return sum;
}

int main(int argc, char ** argv) {

	if (argc < 2) {
		fprintf(stderr, "Usage: ./sbtar file.tar\n");
		exit(1);
	}

	sbtar_t tar;
	sbtar_open(&tar, argv[1]);
	posix_header_t p;
	sbtar_posix(&tar, &p);
	print_posix(p);

	sbtar_ls(&tar);
	sbtar_close(&tar);

	return 0;
}