CC = gcc
CFLAGS = -g -Wall -pedantic

library: loop.o add.o find.o index.o indexbook.o indexdeleted.o delete.o
	$(CC) $(CFLAGS) -o library loop.o add.o find.o index.o indexbook.o indexdeleted.o delete.o

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

indexdeleted.o: indexdeleted.c
	$(CC) $(CFLAGS) -c indexdeleted.c

delete.o: delete.c
	$(CC) $(CFLAGS) -c delete.c

firstfit:
	./library firstfit test

bestfit:
	./library bestfit test

worstfit:
	./library worstfit test

runv:
	valgrind ./library bestfit test

clean:
	rm -rf *.o
	rm library
	rm *.db
	rm *.ind
	rm *.lst
	