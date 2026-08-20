all: main

main: main.o 
	g++ -std=c++11 -Wall -g -o main main.o 

main.o: main.cpp List.h List.cpp
	g++ -std=c++11 -c -g -Wall main.cpp



