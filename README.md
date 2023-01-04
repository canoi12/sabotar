# saboTar

sabotar is a c lib for read and write tar files

load and list
```c
#define SBTAR_IMPLEMENTATION
#include "sabotar.h"

#include <stdio.h>

int main(int argc, char** argv) {
	sbtar_t tar;
	sbtar_load(&tar, "file.tar");
	// find for filename
	if (sbtar_find(&tar, "test.txt")) {
		sbtar_header_t h;
		sbtar_header(&tar, &h);
		printf("size: %d\n", h.size);
	}
	// list all files
	sbtar_ls(&tar);
	sbtar_close(&tar);
	return 0;
}
```

create and write
```c
#define SBTAR_IMPLEMENTATION
#include "sabotar.h"

#include <string.h>

int main(int argc, char** argv) {
	sbtar_t tar;
	sbtar_new(&tar, "file.tar");
	const char* str = "hello world";
	sbtar_write(&tar, "test.txt", str, strlen(str));
	const char* str2 = "sabotar";
	sbtar_write(&tar, "sabotar/sabotar.txt", str2, strlen(str2));
	sbtar_ls(&tar);
	sbtar_close(&tar);
	return 0;
}
```

### References and Inspirations

- [GNU Tar Format](https://www.gnu.org/software/tar/manual/html_node/Standard.html)
- [microtar](https://github.com/rxi/microtar/) *by* [@rxi](https://github.com/rxi/)
- [dxTarRead](https://github.com/DeXP/dxTarRead) *by* [@DeXP](https://github.com/DeXP/)
	- [read tar in 26 lines](https://dexp.in/articles/read-tar-in-26-lines/)