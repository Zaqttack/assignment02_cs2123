# Makefile comments��
PROGRAMS = driver
CC = gcc
CFLAGS = -Wall -g
all: $(PROGRAMS)
clean:
	rm -f *.o
# C compilations
booleanEvaluation.o: booleanEvaluation.c booleanEvaluation.h
	$(CC) $(CFLAGS) -c booleanEvaluation.c
booleanWithError.o: booleanWithError.c booleanWithError.h
	$(CC) $(CFLAGS) -c booleanWithError.c
stack.o: stack.c stack.h booleanWithError.h
	$(CC) $(CFLAGS) -c stack.c
driver.o: driver.c stack.h booleanWithError.h
	$(CC) $(CFLAGS) -c driver.c
# Executable programs
driver: booleanEvaluation.o booleanWithError.o stack.o driver.o
	$(CC) $(CFLAGS) -o driver booleanEvaluation.o booleanWithError.o stack.o driver.o

