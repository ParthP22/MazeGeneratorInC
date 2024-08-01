CC = gcc
CFLAGS = -I./include -Wall -g
LDFLAGS = -L./lib/
LDLIBS = -lmingw32 -l:libglfw3dll.a
OBJ = main.o disjoint_set.o edge_list.o glad.o
HEADERS := include/main.h include/disjoint_set.h include/glad/glad.h include/GLFW/glfw3.h include/GLFW/glfw3native.h 
HEADERS += include/reallocate.h include/edge_list.h

TARGET = main.exe

%.o: ./src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^  $(LDLIBS)
	rm -f $(OBJ)


make clean:
	rm -f %.exe