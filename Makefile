.PHONY: all example example-clean

all: example

example:
	CFLAGS=$(CFLAGS) make -C example

example-clean:
	make -C example clean

check:
	make -C tests

check-clean:
	make -C tests clean