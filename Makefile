CC = gcc
CFLAGS = -g -Wall -pedantic

library: loop.o 
	$(CC) $(CFLAGS) -o library loop.o

loop.o: loop.c
	$(CC) $(CFLAGS) -c loop.c

run:
	./library

clean:
	rm -rf *.o