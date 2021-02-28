#include "src/sbtar.h"

int main(int argc, char ** argv) {

	sbtar_t tar;
	sbtar_open(&tar, "teste.tar");

	sbtar_header_t h;
	/*sbtar_find(&tar, &h, argv[1]);*/
	sbtar_find(&tar, argv[1] ? argv[1] : "teste.txt");
	sbtar_header(&tar, &h);

	/*long sz = sbtar_header_size(&h);*/
	char buf[h.size+1];
	/*sbtar_read(&tar, &h, buf);*/
	sbtar_data(&tar, buf, h.size);
	buf[h.size] = '\0';
	printf("%s\n", buf);

	sbtar_ls(&tar);

	/*printf("%s - %d: %s\n", h.name, h.type, buf);*/

	sbtar_close(&tar);

	return 0;
}