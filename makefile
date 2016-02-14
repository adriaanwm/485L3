sort: sort.o 
	g++ -o sort sort.o

sort.o: sort.cpp
	g++ -c sort.cpp

heap: heap.o
	g++ -o heap heap.o

heap.o: heap.cpp
	g++ -c heap.cpp

bump:	bump.o heap.o
	g++ -o bump bump.o heap.o

bump.o:	heap.h bump.cpp
	g++ -c bump.cpp
