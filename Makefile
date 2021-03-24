CC = gcc
CFLAGS = -Wall -Wextra -g3
OFLAGS = -O2

build: target
	$(CC) $(CFLAGS) $(OFLAGS) src/*.c -o target/main

run: build
	target/main -m 10000 100 100
	target/main -c 10000 100 100

gdb: build
	gdb target/main -m 1000 100 100

vg_m: build
	valgrind --leak-check=full -v target/main -m 10000 100 100

vg_c: build
	valgrind --leak-check=full -v target/main -c 10000 100 100

target:
	mkdir -p target

clean:
	rm -Rf target
