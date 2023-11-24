CC = gcc
CFLAGS = -g -Wall -pedantic

library: loop.o add.o library.o book.o
	$(CC) $(CFLAGS) -o library loop.o add.o library.o book.o

loop.o: loop.c
	$(CC) $(CFLAGS) -c loop.c

add.o: add.c
	$(CC) $(CFLAGS) -c add.c

library.o: library.c
	$(CC) $(CFLAGS) -c library.c

book.o: book.c
	$(CC) $(CFLAGS) -c book.c

run:
	./library

clean:
	rm -rf *.o