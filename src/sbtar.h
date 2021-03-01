#ifndef SABOTAR_H
#define SABOTAR_H

#define SBTAR_API extern

#define SBTAR_VERSION "0.1.0"

#ifndef SBTAR_MALLOC
  #define SBTAR_MALLOC malloc
#endif

#define STR(x) #x
#define SBTAR_ASSERT(expr) \
  if (!(expr)) { \
    fprintf(stderr, "Assertion failed: %s\n", STR(expr)); \
    exit(1); \
  }

#define SBTAR_NAME_OFFSET     0
#define SBTAR_MODE_OFFSET     100
#define SBTAR_UID_OFFSET      108
#define SBTAR_GID_OFFSET      116
#define SBTAR_SIZE_OFFSET     124
#define SBTAR_MTIME_OFFSET    136
#define SBTAR_CHKSUM_OFFSET   148
#define SBTAR_TYPE_OFFSET     156
#define SBTAR_LINKNAME_OFFSET 157
#define SBTAR_MAGIC_OFFSET    257
#define SBTAR_VERSION_OFFSET  263
#define SBTAR_UNAME_OFFSET    265
#define SBTAR_GNAME_OFFSET    297
#define SBTAR_DEVMAJ_OFFSET   329
#define SBTAR_DEVMIN_OFFSET   337
#define SBTAR_PREFIX_OFFSET   345

#define TMAGIC "ustar"

#define SBTAR_BLOCK_SIZE 512
#define SBTAR_NAME_SIZE 100
#define SBTAR_SZ_SIZE 12
#define SBTAR_MAGIC_SIZE 5

#include <stdio.h>
#include <stdlib.h>

enum {
  SBTAR_TREG = 0,
  SBTAR_TLINK,
  SBTAR_TSYM,
  SBTAR_TCHR,
  SBTAR_TBLK,
  SBTAR_TDIR,
  SBTAR_TFIFO
};

typedef struct sbtar_t sbtar_t;
typedef struct sbtar_header_t sbtar_header_t;
typedef struct posix_header_t posix_header_t;

struct sbtar_t {
  unsigned offset;
  unsigned size;

  FILE *fp;
};

struct sbtar_header_t {
  unsigned size;
  unsigned mode;
  unsigned type;
  unsigned mtime;
  char name[100];
  char linkname[100];
  char uname[32], gname[32];
};

SBTAR_API void sbtar_open(sbtar_t *tar, const char *filename);
SBTAR_API void sbtar_close(sbtar_t *tar);

SBTAR_API int sbtar_next(sbtar_t *tar);
SBTAR_API void sbtar_rewind(sbtar_t *tar);
SBTAR_API void sbtar_seek(sbtar_t *tar, unsigned offset);

SBTAR_API void sbtar_header(sbtar_t *tar, sbtar_header_t *h);
SBTAR_API void sbtar_data(sbtar_t *tar, void *buf, unsigned size);

SBTAR_API void sbtar_ls(sbtar_t *tar);
SBTAR_API int sbtar_find(sbtar_t *tar, const char *filename);

SBTAR_API const char* sbtar_read(sbtar_t *tar, const char *filename);
SBTAR_API void sbtar_write(sbtar_t *tar, const char *filename, const char *text, unsigned size);
SBTAR_API void sbtar_write_dir(sbtar_t *tar, const char *dirname);
/*SBTAR_API void sbtar_write(sbtar_t *tar, const char *file, const char *text);*/

#endif /* SABOTAR */