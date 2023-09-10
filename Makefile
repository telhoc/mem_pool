program_NAME := mempool

SRCS = memory.c
OBJS := ${SRCS:.c=.o}

.PHONY: all

CFLAGS = -Wall -ggdb
CC := gcc

all: $(program_NAME)

$(program_NAME): $(OBJS)
	@$(CC) -c $(CFLAGS) $(OBJS)
	ar rcs libmempool.a memory.o
	gcc -o $(program_NAME) test.c -L. -lmempool

clean:
	rm -rf *.o $(program_NAME) mempool.a
