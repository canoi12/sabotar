CC = gcc
AR = ar

OUT = sbtar

SRC = src/*.c
INCLUDE =
CFLAGS = -std=c89 -Wall

LIBNAME = lib$(OUT)

OBJS = $(SRC:%.c=%.o)

$(OUT): main.c $(LIBNAME).a
	$(CC) main.c -o $(OUT) -L. -l$(OUT) $(INCLUDE) $(CFLAGS) $(INCLUDE)

$(LIBNAME).a: $(OBJS)
	$(AR) rcs $(LIBNAME).a src/*.o

%.o: %.c
	$(CC) -c $< -o $@ $(INCLUDE) $(CFLAGS)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
	rm -f $(LIBNAME).a
	rm -f $(OBJS)
