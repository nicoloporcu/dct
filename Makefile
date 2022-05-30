CC= g++

all : main.cpp dct.o
	$(CC) main.cpp dct.o -Wall  -o  dct

dct.o : dct.cpp dct.h
	$(CC) dct.cpp -Wall -c -o  dct.o
