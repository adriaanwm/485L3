sort: sort.o 
	g++ -o sort sort.o

sort.o: sort.cpp
	g++ -c sort.cpp

heap: heap.o
	g++ -o heap heap.o

heap.o: heap.cpp
	g++ -c heap.cpp

