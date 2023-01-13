CC=clang++
CXXFLAGS=-g -Wall -std=c++17
LFLAGS=-lpthread
SHELL=/bin/bash

.PHONY: all build debug run

build: src/main.cpp

	make create_build_dir
	[ -d build ] && [ -f src/main.cpp ] && $(CC) -o build/main.elf $(CXXFLAGS) src/main.cpp $(LFLAGS)

create_build_dir:

	[ -d build ] || mkdir build

run:
	[ -f build/main.elf ] && ./build/main.elf


debug:

	gdb build/main.elf