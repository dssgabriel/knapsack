CC = gcc
CFLAGS = -Wall -Wextra -g3
OFLAGS = -O2

build: target
	$(CC) $(CFLAGS) $(OFLAGS) src/common.c src/algorithm.c src/bin/main.c -o target/main

run: build
	target/main -m 100000 100 100
	target/main -c 100000 100 100

gdb: build
	gdb target/main matrix 1000 100 100

vg_m: build
	valgrind --leak-check=full -v target/main matrix 10000 100 100

vg_c: build
	valgrind --leak-check=full -v target/main csr 10000 100 100

target:
	mkdir -p target

clean:
	rm -Rf target
