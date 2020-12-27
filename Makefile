CC = gcc
CFLAGS = -Wall -Wextra -g3
OFLAGS = -O2
DEP = src/common.c

build: target
	$(CC) $(CFLAGS) $(OFLAGS) src/common.c src/algorithm.c src/bin/main.c -o target/main

run: build
	target/main 1000 100 100

gdb: build
	gdb target/main 1000 100 100

vg: build
	valgrind --leak-check=full -v target/main 1000 100 100

target:
	mkdir -p target

clean:
	rm -Rf target
