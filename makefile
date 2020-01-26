CC=gcc
FLAGS= -Wall -g

all: frequency
frequency: frequency.c frequency.h
	$(CC) $(FLAGS)  frequency.c frequency.h -o frequency

.PHONY: clean all

clean:
	rm -f frequency
