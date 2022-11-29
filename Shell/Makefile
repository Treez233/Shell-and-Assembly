CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -Wextra -pedantic-errors -fstack-protector-all

all: d8sh

lexer.o: lexer.c
	$(CC) $(CFLAGS) -c lexer.c

parser.tab.o: parser.tab.c parser.tab.h command.h
	$(CC) $(CFLAGS) -c parser.tab.c 

executor.o: executor.c executor.h command.h
	$(CC) $(CFLAGS) -c executor.c 

d8sh: lexer.o parser.tab.o executor.o d8sh.o
	$(CC) -lreadline -o d8sh d8sh.o lexer.o parser.tab.o executor.o 

d8sh.o: d8sh.c executor.h lexer.h
	$(CC) $(CFLAGS) -lreadline -c d8sh.c 


clean:
	@echo "Poof"
	@rm -f d8sh *.o *.tmp