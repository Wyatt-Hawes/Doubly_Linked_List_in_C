CC = gcc
CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g#$(shell pkg-config --cflags)

all: ListTest Lex

Lex: Lex.o List.o
	$(CC) -o $@ $^

List: List.o
	$(CC) -o $@ $^
	
ListTest: ListTest.o List.o 

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean: spotless
	rm -f *.o
	
spotless: clean
	rm -f ListTest Lex
