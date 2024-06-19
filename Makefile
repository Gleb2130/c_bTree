CC = gcc

CFLAGS = -Wall -Wextra -g

OBJ = main.o BTree_realization.o

TARGET = btree_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

main.o: main.c BTree.h
	$(CC) $(CFLAGS) -c main.c

BTree_realization.o: BTree_realization.c BTree.h
	$(CC) $(CFLAGS) -c BTree_realization.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
