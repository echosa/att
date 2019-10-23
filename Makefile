att: main.c
	gcc -Wall -Wextra -ansi -pedantic -std=c99 -o att main.c
install:
	cp att /usr/local/bin
