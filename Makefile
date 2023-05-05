CC = gcc
CFLAGS= -I ./unity/src/ -I ./include/
SRC_DIRS = ./src

sources := $(wildcard $(SRC_DIRS)/*.c)

compile:
	$(CC) $(CFLAGS) -o ls $(sources)

runtest:
	$(CC) $(CFLAGS) -o test.o test/output.c ./unity/src/unity.c
	./test.o
