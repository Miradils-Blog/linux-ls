CC = gcc
CFLAGS= -I ./unity/src/ -I ./include/ -fms-extensions
SRC_DIRS = ./src
TESTS_DIR = ./tests

sources := $(wildcard $(SRC_DIRS)/*.c)
tests := $(wildcard $(TESTS_DIR)/*.c)

compile:
	$(CC) $(CFLAGS) -o ls $(sources)

runtest:
	for test in $(tests) ; do \
		$(CC) $(CFLAGS) -o test.o $$test ./unity/src/unity.c && ./test.o; \
	done
