CC = gcc
CFLAGS = -g -Wall -pedantic

library: loop.o add.o library.o indexbook.o book.o
	$(CC) $(CFLAGS) -o library loop.o add.o library.o indexbook.o book.o

loop.o: loop.c
	$(CC) $(CFLAGS) -c loop.c

add.o: add.c
	$(CC) $(CFLAGS) -c add.c

library.o: library.c
	$(CC) $(CFLAGS) -c library.c

indexbook.o: indexbook.c
	$(CC) $(CFLAGS) -c indexbook.c

book.o: book.c
	$(CC) $(CFLAGS) -c book.c

run:
	./library bestfit test

runv:
	valgrind ./library bestfit test

clean:
	rm -rf *.o