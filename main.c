#include "src/sbtar.h"

int main(int argc, char ** argv) {

	if (argc < 2) {
		fprintf(stderr, "Usage: ./sbtar file.tar\n");
		exit(1);
	}

	sbtar_t tar;
	sbtar_open(&tar, argv[1]);
	sbtar_ls(&tar);
	sbtar_close(&tar);

	return 0;
}