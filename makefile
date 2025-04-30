CFLAGS = -Wall -Wextra -g -std=c99
CC = gcc

TARGET = myrb 

SRCS = main.c tree.c
HEADERS = tree.h

all: main.o tree.o
	$(CC) $(CFLAGS) main.c tree.c -o $(TARGET)

tree.o: tree.h
	$(CC) $(CFLAGS) -c tree.c -o tree.o
	
main.o: tree.h
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm -f *.o
