att: *.c
	clang -Wall -Wextra -pedantic -o att *.c
debug: *.c
	clang -g -O0 -Wall -Wextra -pedantic -o att *.c
tests: tests.c main.c
	clang -Wall -Wextra -pedantic -l cmocka -o tests tests.c \
    && ./tests \
    ; rm tests
install:
	cp att /usr/local/bin
uninstall:
	rm /usr/local/bin/att
check-syntax:
	clang -o /dev/null -l cmocka -S ${CHK_SOURCES}
