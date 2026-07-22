CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

.PHONY: all clean

all: hexdump

hexdump: src/main.c src/hexdump.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f hexdump *.o
