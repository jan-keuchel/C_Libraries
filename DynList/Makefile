CC=gcc
CFLAGS=-Wall -g -fPIC
LDFLAGS=-shared
BINS=librarytest libdynlist.so
LIBNAME=dynlist
PREFIX=/usr
INCLUDEDIR=$(PREFIX)/include
LIBDIR=$(PREFIX)/lib

all: $(BINS)

libdynlist.o: dynlist.c dynlist.h 
	$(CC) $(CFLAGS) -c dynlist.c -o libdynlist.o

libdynlist.so: libdynlist.o 
	$(CC) $(LDFLAGS) -o $@ $< -lc

librarytest: main.c libdynlist.o 
	$(CC) $(CFLAGS) -o $@ $^

install: libdynlist.so dynlist.h
	install -d $(INCLUDEDIR)
	install -m 644 dynlist.h $(INCLUDEDIR)
	install -d $(LIBDIR)
	install -m 755 libdynlist.so $(LIBDIR)
	ldconfig

clean: 
	rm -f *.o $(BINS)

.PHONY: all install clean
