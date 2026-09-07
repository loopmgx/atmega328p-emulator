CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -g -O0

OBJ = build/main.o

all: a.out

a.out: $(OBJ)
	$(CC) $(OBJ) -o a.out

build:
	mkdir -p build

build/main.o: main.c | build
	$(CC) $(CFLAGS) -c main.c -o build/main.o




clean:
	rm -rf build a.out
