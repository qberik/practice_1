CC=g++

all: build

build:
	$(CC) main.cpp menu.cpp input.cpp table.cpp value.cpp string.cpp -o DB


clean:
	rm -rf DB
