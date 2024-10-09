CC = gcc

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

.PHONY: clean all

all: coolness

coolness: $(OBJECTS)
	$(CC) -o $@ $^ -lm

%.o: %.c
	$(CC) -c $<

clean:
	rm -f $(OBJECTS) coolness
