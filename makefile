CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -Wsign-conversion -DWARNING_MODE -g -O0

OBJ = build/main.o    \
	  build/vm.o	  \
	  build/error.o   \
	  build/flags.o   \
	  build/loader.o  \


CFLAGS_TEST = -Wall -Wextra -Wconversion -Wsign-conversion -DWARNING_MODE -g -O0

TEST_OBJ = build/main_test.o     \
		   build/error_test.o    \
		   build/loader.o        \
		   build/loader_test.o   \

all: a.out

a.out: $(OBJ)
	$(CC) $(OBJ) -o a.out

build:
	mkdir -p build

build/main.o: main.c | build
	$(CC) $(CFLAGS) -c main.c -o build/main.o

build/vm.o: src/vm.c | build
	$(CC) $(CFLAGS) -c src/vm.c -o build/vm.o

build/error.o: src/error.c | build
	$(CC) $(CFLAGS) -c src/error.c -o build/error.o

build/flags.o: src/flags.c | build
	$(CC) $(CFLAGS) -c src/flags.c -o build/flags.o

build/loader.o: src/loader.c | build
	$(CC) $(CFLAGS) -c src/loader.c -o build/loader.o


# TESTS
# ////////////////////////////////////////////////////////////

test: $(TEST_OBJ) | build
	$(CC) $(CFLAGS_TEST) $(TEST_OBJ) -o a.out

build/main_test.o: tests/main_test.c | build
	$(CC) $(CFLAGS_TEST) -c tests/main_test.c -o build/main_test.o

build/loader_test.o: tests/loader/loader_test.c | build
	$(CC) $(CFLAGS_TEST) -c tests/loader/loader_test.c -o build/loader_test.o

build/error_test.o: src/error.c | build
	$(CC) $(CFLAGS_TEST) -c src/error.c -o build/error_test.o


clean:
	rm -rf build a.out
