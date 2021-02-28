#include "sbtar.h"

#include <string.h>

/* POSIX header */
union posix_header_t {
	struct {
		char name[100];
		char mode[8];
		char uid[8];
		char gid[8];
		char size[12];
		char mtime[12];
		char chksum[8];
		char typeflag;
		char linkname[100];
		char magic[6];
		char version[2];
		char uname[32];
		char gname[32];
		char devmajor[8];
		char devminor[8];
		char prefix[155];
	};
	char data[SBTAR_BLOCK_SIZE];
};

long _header_size(const posix_header_t *h) {
	SBTAR_ASSERT(h != NULL);
	const char *sz = h->size;
	long size = 0;
	int i, mul;
	for (i = SBTAR_SZ_SIZE - 2, mul = 1; i >= 0; mul*=8,i--)
		if ( (sz[i] >= '1') && (sz[i] < '8')) size += (sz[i] - '0') * mul;

	return size;
}

void sbtar_open(sbtar_t *tar, const char *filename) {
	SBTAR_ASSERT(tar != NULL);

	tar->fp = fopen(filename, "rb+");
	if (!tar->fp) {
		fprintf(stderr, "Failed to open %s\n", filename);
		exit(1);
	}
	tar->offset = 0;
	fseek(tar->fp, 0, SEEK_END);
	tar->size = ftell(tar->fp);
	fseek(tar->fp, 0, SEEK_SET);
}

void sbtar_close(sbtar_t *tar) {
	SBTAR_ASSERT(tar != NULL);

	fclose(tar->fp);
	tar->offset = 0;
}

int sbtar_next(sbtar_t *tar) {
	SBTAR_ASSERT(tar != NULL);
	sbtar_header_t h;
	sbtar_header(tar, &h);

	int next = (1 + h.size/SBTAR_BLOCK_SIZE) * SBTAR_BLOCK_SIZE;
	/*printf("%d\n", h.type + 1);*/
	int type = h.type;
	if (type < 0 || (tar->offset + next >= tar->size)) return 0;
	if (h.size != 0) next += SBTAR_BLOCK_SIZE;
	sbtar_seek(tar, tar->offset + next);

	return 1;
}

void _print_header(sbtar_header_t h) {
	printf("%s::%d - %db\n", h.name, h.type, h.size);
}

void sbtar_ls(sbtar_t *tar) {
	sbtar_rewind(tar);
	sbtar_header_t h;
	sbtar_header(tar, &h);

	while (sbtar_next(tar)) {
		_print_header(h);
		sbtar_header(tar, &h);
	}

	sbtar_rewind(tar);
}

void sbtar_rewind(sbtar_t *tar) {
	sbtar_seek(tar, 0);
}

void sbtar_seek(sbtar_t *tar, unsigned offset)	{
	SBTAR_ASSERT(tar != NULL);
	tar->offset = offset;
	fseek(tar->fp, tar->offset, SEEK_SET);
}

void sbtar_header(sbtar_t *tar, sbtar_header_t *header) {
	SBTAR_ASSERT(tar != NULL);
	SBTAR_ASSERT(header != NULL);
	sbtar_header_t *h = header;

	posix_header_t posix;
	fread(posix.data, SBTAR_BLOCK_SIZE, 1, tar->fp);
	strcpy(h->name, posix.name);
	strcpy(h->linkname, posix.linkname);
	h->size = _header_size(&posix);
	h->type = posix.typeflag - '0';

	sbtar_seek(tar, tar->offset);
}

void sbtar_data(sbtar_t *tar, void *ptr, unsigned size) {
	char *buffer = ptr;

	sbtar_seek(tar, tar->offset + SBTAR_BLOCK_SIZE);

	/*long sz = sbtar_header_size(header);*/
	/*long sz = header->size;*/

	/*int bl_sz = (1 + sz/SBTAR_BLOCK_SIZE) * SBTAR_BLOCK_SIZE;*/

	/*char buf[sz+1];*/
	fread(buffer, size, 1, tar->fp);
	buffer[size] = '\0';

	sbtar_seek(tar, tar->offset - SBTAR_BLOCK_SIZE);
}

int sbtar_find(sbtar_t *tar, const char *filename) {
	SBTAR_ASSERT(tar != NULL);
	/*SBTAR_ASSERT(header != NULL);*/
	SBTAR_ASSERT(filename != NULL);

	/*fseek(tar->fp, 0, SEEK_END);
	size_t size = ftell(tar->fp);

	sbtar_seek(tar, 0);*/

	sbtar_rewind(tar);

	sbtar_header_t h;
	sbtar_header(tar, &h);
	if (!strcmp(h.name, filename)) return 1;

	while (sbtar_next(tar)) {
		sbtar_header(tar, &h);
		if (!strcmp(h.name, filename)) return 1;
	}

	printf("file %s not found\n", filename);
	return 0;
}

const char* sbtar_read(sbtar_t *tar, const char *filename) {
	SBTAR_ASSERT(tar != NULL);
	SBTAR_ASSERT(filename != NULL);



	/*tar->offset += SBTAR_BLOCK_SIZE;
	fseek(tar->fp, tar->offset, SEEK_SET);

	long sz = header->size;

	int bl_sz = (1 + sz/SBTAR_BLOCK_SIZE) * SBTAR_BLOCK_SIZE;

	fread(out, sz, 1, tar->fp);
	out[sz] = '\0';*/
	return NULL;
}

void sbtar_write(sbtar_t *tar, const char *filename, const char *text, unsigned size) {

}
void sbtar_write_dir(sbtar_t *tar, const char *dirname) {

}