att: main.c
	clang -Wall -Wextra -pedantic -o att main.c
debug: main.c
	clang -g -O0 -Wall -Wextra -pedantic -o att main.c
install:
	cp att /usr/local/bin
uninstall:
	rm /usr/local/bin/att
check-syntax:
	clang -o /dev/null -S ${CHK_SOURCES}
