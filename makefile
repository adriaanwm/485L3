CC = g++
OBJ = bump.cpp \
      maxheap.cpp \
      element.cpp \
			lexlabel.cpp \
			parse_poset_file.cpp

All: $(OBJ)
	$(CC) $(OBJ) -o bump
