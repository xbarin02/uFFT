CFLAGS=-std=c99 -pedantic -Wall -Wextra -Wconversion -D_XOPEN_SOURCE -march=native -O3
LDLIBS=-lm

.PHONY: all
all: example-dit-dit.out example-dit-dif.out example-dif-dit.out example-dif-dif.out

example-dit-dit.out: example.o libfft-dit.a libift-dit.a

example-dit-dif.out: example.o libfft-dit.a libift-dif.a

example-dif-dit.out: example.o libfft-dif.a libift-dit.a

example-dif-dif.out: example.o libfft-dif.a libift-dif.a

%.out:
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

lib%.a: %.o
	$(AR) -rs $@ $^

.PHONY: clean
clean:
	$(RM) -- *.out *.a *.o
