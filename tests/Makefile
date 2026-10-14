# Run everything:   make -C tests        (or: cd tests && make)
P00 = ../challenges/project00
P01 = ../challenges/project01
CC = gcc
CFLAGS = -g -Wall -Werror -I$(P01)
LIBS = -lm
P01_OBJS = $(patsubst %.c,%.o,$(filter-out $(P01)/main.c,$(wildcard $(P01)/*.c)))

.PHONY: test all build unit models clean

test all: build unit models

build:
	@$(MAKE) -s -C $(P00) CFLAGS="-g -Wall -Werror"
	@$(MAKE) -s -C $(P01) CFLAGS="-g -Wall -Werror"

unit_tests: unit_tests.c build
	@$(CC) $(CFLAGS) -o $@ unit_tests.c $(P01_OBJS) $(LIBS)

unit: unit_tests
	@./unit_tests

models: build
	@bash ./model_tests.sh

clean:
	-rm -f unit_tests
	@$(MAKE) -s -C $(P00) clean
	@$(MAKE) -s -C $(P01) clean
