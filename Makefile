CC = gcc
AR = ar

OUT = sbtar

SRC = sabotar.c
INCLUDE =
CFLAGS = -std=c89 -Wall -g

LIBNAME = lib$(OUT)

OBJS = $(SRC:%.c=%.o)

$(OUT): main.c $(LIBNAME).a
	$(CC) main.c -o $(OUT) -L. -l$(OUT) $(INCLUDE) $(CFLAGS) $(INCLUDE)

$(LIBNAME).a: sabotar.h $(OBJS)
	$(AR) rcs $(LIBNAME).a $(OBJS)

%.o: %.c %.h
	$(CC) -c $< -o $@ $(INCLUDE) $(CFLAGS)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
	rm -f $(LIBNAME).a
	rm -f $(OBJS)
