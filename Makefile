CC = gcc
AR = ar

NAME = sbtar
OUT = $(NAME)

RELEASE ?= 0

SRC = sabotar.c
INCLUDE =
CFLAGS = -std=c89 -Wall

ifeq ($(RELEASE),1)
	CFLAGS += -O2
else
	CFLAGS += -g
endif

LIBNAME = lib$(NAME)
SLIBNAME = $(LIBNAME).a
DLIBNAME = $(LIBNAME).so

OBJS = $(SRC:%.c=%.o)
DOBJS = $(SRC:%.c=%.do)

.PHONY: build all

build: $(OUT)

all: $(SLIBNAME) $(DLIBNAME)

$(OUT): main.c $(LIBNAME).a
	$(CC) main.c -o $(OUT) -L. -l$(OUT) $(INCLUDE) $(CFLAGS) $(INCLUDE)

$(SLIBNAME): $(OBJS)
	$(AR) rcs $@ $^

$(DLIBNAME): $(DOBJS)
	$(CC) -shared -o $@ $< $(INCLUDE) $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $< -o $@ $(INCLUDE) $(CFLAGS)

%.do: %.c %.h
	$(CC) -fPIC -c $< -o $@ $(INCLUDE) $(CFLAGS)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
	rm -f $(SLIBNAME) $(DLIBNAME)
	rm -f $(OBJS) $(DOBJS)
