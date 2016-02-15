all: sort heap bump

sort: sort.o 
	g++ -o sort sort.o

sort.o: sort.cpp
	g++ -c sort.cpp

heap: heap.o
	g++ -o heap heap.o

heap.o: heap.cpp
	g++ -c heap.cpp

bump:	bump.o maxheap.o
	g++ -o bump bump.o maxheap.o

bump.o:	maxheap.h bump.cpp
	g++ -c bump.cpp

quicktest: quicktest.o
	g++ -o quicktest quicktest.o

quicktest.o: quicktest.cpp
	g++ -c quicktest.cpp
