CC = gcc
AR = ar

OUT = sbtar

RELEASE ?= 0

SRC = sabotar.c
INCLUDE =
CFLAGS = -std=c89 -Wall

ifeq ($(RELEASE),1)
	CFLAGS += -O2
else
	CFLAGS += -g
endif

LIBNAME = lib$(OUT)

OBJS = $(SRC:%.c=%.o)
DOBJS = $(SRC:%.c=%.do)

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
