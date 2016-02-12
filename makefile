sort: sort.o 
	g++ -o sort sort.o

sort.o: sort.cpp
	g++ -c sort.cpp
