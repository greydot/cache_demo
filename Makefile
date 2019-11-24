CC=clang
CFLAGS=-std=c11 -Wall -pedantic -ggdb3
LDFLAGS=-lnuma

cache: cache.o
	$(CC) -o $@ $< $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o cache

.PHONY: clean
