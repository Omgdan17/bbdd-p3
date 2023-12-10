CC = gcc
CFLAGS = -g -Wall -pedantic

library: loop.o add.o find.o index.o indexbook.o
	$(CC) $(CFLAGS) -o library loop.o add.o find.o index.o indexbook.o

loop.o: loop.c
	$(CC) $(CFLAGS) -c loop.c

add.o: add.c
	$(CC) $(CFLAGS) -c add.c

find.o: find.c
	$(CC) $(CFLAGS) -c find.c

index.o: index.c
	$(CC) $(CFLAGS) -c index.c

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
	rm library
	rm *.ind
	rm *.lst
	rm *.db