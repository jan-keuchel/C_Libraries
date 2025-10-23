CC=gcc
CFLAGS=-Wall -g -fPIC
LDFLAGS=-shared
BINS=librarytest libbbst.so
LIBNAME=bbst
PREFIX=/usr
INCLUDEDIR=$(PREFIX)/include
LIBDIR=$(PREFIX)/lib

all: $(BINS)

libbbst.o: bbst.c bbst.h 
	$(CC) $(CFLAGS) -c bbst.c -o libbbst.o

libbbst.so: libbbst.o 
	$(CC) $(LDFLAGS) -o $@ $< -lc

librarytest: main.c libbbst.o 
	$(CC) $(CFLAGS) -o $@ $^

debug: main.c libbbst.o
	$(CC) $(CFLAGS) -o $@ $^

runvalgrind: debug
	valgrind --leak-check=full --show-leak-kinds=definite ./debug

install: libbbst.so bbst.h
	install -d $(INCLUDEDIR)
	install -m 644 bbst.h $(INCLUDEDIR)
	install -d $(LIBDIR)
	install -m 755 libbbst.so $(LIBDIR)
	ldconfig

clean: 
	rm -f *.o $(BINS)

.PHONY: all install clean
