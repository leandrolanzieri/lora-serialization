# Force double precision with floating point operations
LFLAGS = -msse2 -mfpmath=sse

CHECK_LIBS = `pkg-config --cflags --libs check`
CFLAGS += -I../ -fprofile-arcs -ftest-coverage
LDFLAGS += -fprofile-arcs -ftest-coverage $(CHECK_LIBS)
TARGET = check

.PHONY: all

all: $(TARGET) run gcov

check: check_lora_serialization.o lora_serialization.o
	gcc *.o $(LDFLAGS) -o $(TARGET)

check_lora_serialization.o: *.c
	gcc $(CFLAGS) -c $< -o $@

lora_serialization.o: ../*.c
	gcc $(LFLAGS) $(CFLAGS) -c $< -o $@

run:
	$(CURDIR)/check

gcov:
	gcov ../*.c --object-directory=$(CURDIR)

clean:
	rm -f *.o *.gc $(TARGET)