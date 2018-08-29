CFLAGS += -I../

# Force double precision with floating point operations
LFLAGS = -msse2 -mfpmath=sse

.PHONY: all

all: example

example: main.o lora_serialization.o
	gcc -o example main.o lora_serialization.o

main.o: main.c
	gcc $(CFLAGS) -c $< -o $@

lora_serialization.o: ../lora_serialization.c
	gcc $(LFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o example