.PHONY: default help object executable all clean
CC = gcc

LD = $(CC)

SOURCE_C = $(wildcard *.c)
OBJECTS_C = $(patsubst %.c, ../bin/%_c.o, $(SOURCE_C))

CFLAGS = -std=gnu99 -O3
EXECUTABLE = ../bin/ising.e

default: help

help:
	@echo "\
Options:\n\n\
  make objects:       compiler makes objects for every *.c\n\
  make executable:    compiler makes executable\n\
  make all:           build all previous\n\
  make clean:         delete output files\n\
  make help:          display this help"

objects: $(OBJECTS_C)

executable: $(EXECUTABLE)

all: objects executable

../bin/%_c.o: %.c
	$(CC) $(CFLAGS) -c $^ -o ../bin/$@ -lm

%.e: $(OBJECTS_C)
	$(LD) $^ -o $@ -lm

clean:
	rm -rfv $(OBJECTS_C) $(EXECUTABLE)
