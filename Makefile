# Variables
CC=gcc
CFLAGS=-std=c11 -Werror -Wall
LDLIBS=-lcurses
OUTPUT=ps2

.PHONY: all clean

# Tasks
all: $(OUTPUT)

$(OUTPUT): main.o hof.o k.o ui.o
	cppcheck --check-level=exhaustive --enable=performance unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(OUTPUT)
