.PHONY: all example example-clean

all: example

example:
	CFLAGS=$(CFLAGS) make -C examples

example-clean:
	make -C examples clean

check:
	make -C tests

check-clean:
	make -C tests clean