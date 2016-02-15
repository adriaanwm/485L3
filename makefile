CC = g++
OBJ = bump.cpp \
      maxheap.cpp \
      element.cpp 

All: $(OBJ)
	$(CC) $(OBJ)  $(LDLIBS) -o lex
