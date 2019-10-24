att: main.c
	clang -Wall -Wextra -pedantic -o att main.c
install:
	cp att /usr/local/bin
uninstall:
	rm /usr/local/bin/att
check-syntax:
	clang -o nul -S ${CHK_SOURCES}
