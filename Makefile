CC = gcc
CFLAGS = -I./include -Wall -g
LDFLAGS = -L./lib/
LDLIBS = -lmingw32 -lraylib -lgdi32 -lwinmm 
OBJ = main.o disjoint_set.o edge.o edge_list.o maze_generator.o
HEADERS := include/main.h include/disjoint_set.h include/maze_generator.h
HEADERS += include/raylib.h include/raymath.h include/rlgl.h include/reallocate.h include/edge_list.h include/edge.h

TARGET = main.exe

%.o: ./src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^  $(LDLIBS)
	rm -f $(OBJ)


make clean:
	rm -rf %.exe