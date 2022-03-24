TARGET = challenge01 challenge02 challenge03 challenge04 challenge05 challenge06 challenge07

LIBS = -lm
CC = gcc
CFLAGS = -g -Wall
OBJS = markov.o

.PHONY: default all clean

default: $(TARGET)
all: default

markov.o: markov.c
	$(CC) $(CFLAGS) -c $< $(LIBS)

$(TARGET): %: %.c $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	-rm -f *.o
	-rm -f $(TARGET)
