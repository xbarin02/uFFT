CFLAGS=-std=c99 -pedantic -Wall -Wextra -Wconversion -D_XOPEN_SOURCE -march=native -O3
LDLIBS=-lm

example: libufft.a

libufft.a: ufft.o
	$(AR) -rs $@ $^
