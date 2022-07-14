.PHONY: clean
CC=clang
CFLAGS=-g --std=c11 -fpic

all: binarycalc

binarycalc: binarycalc.o
	$(CC) -Wall -o $@ $^

binarycalc.o: binarycalc.c
	$(CC) -c -Wall -o $@ $< $(CFLAGS)

clean:
	rm -f binarycalc.o binarycalc