CC=clang++
CXXFLAGS=-g -Wall -std=c++2a
LFLAGS=-lpthread
SHELL=/bin/bash

.PHONY: all build debug run test

build: src/main.cpp

	make create_build_dir
	[ -d build ] && [ -f src/main.cpp ] && \
		$(CC) $(CXXFLAGS) -o build/main.elf \
			src/main.cpp $(LFLAGS)

test: test/test.cpp

	[ -d build ] || exit
	$(CC) $(CXXFLAGS) -o build/test test/test.cpp
	./build/test
	

create_build_dir:

	[ -d build ] || mkdir build

run:
	[ -f build/main.elf ] && ./build/main.elf


clean:

	[ -d build/ ] && rm build/*


debug:

	gdb build/main.elf