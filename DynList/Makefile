CC=gcc
CFLAGS=-Wall -g
BINS=librarytest libdynlist.so


all: $(BINS)

libdynlist.o: dynlist.c dynlist.h
	$(CC) $(CFLAGS) -c dynlist.c

libdynlist.so: dynlist.o dynlist.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ dynlist.c -lc

librarytest: main.c dynlist.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o $(BINS)
