CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = main.c wagon.c array_helpers.c
OBJECTS = $(SOURCES:.c=.o)
INPUT_PATH=input
TESTFILES = $(shell ls ${INPUT_PATH})
TARGET = train

.PHONY: clean

all: $(TARGET)

test: $(TARGET) $(TESTFILES)

valgrind: $(TARGET) $(TESTFILES:.in=.val)

%.in:
	@echo "Testing $*...\n"
	./$(TARGET) ${INPUT_PATH}/$*.in
	@echo "\n\n"

%.val:
	@echo "Testing $*...\n"
	valgrind --error-exitcode=2 --leak-check=full ./$(TARGET) ${INPUT_PATH}/$*.in
	@echo "\n\n"


$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)

