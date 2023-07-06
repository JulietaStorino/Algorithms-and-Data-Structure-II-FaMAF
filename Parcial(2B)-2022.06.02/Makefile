CC = gcc
VG = valgrind
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = pstack.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = pstack_test
INPUT = ./inputs/example_

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)

valid.a:
	$(VG) ./$(TARGET) $(INPUT)a.in

valid.b:
	$(VG) ./$(TARGET) $(INPUT)b.in
	
valid.c:
	$(VG) ./$(TARGET) $(INPUT)c.in