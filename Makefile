att: src/*.c
	clang -Wall -Wextra -pedantic -o att src/*.c
debug: src/*.c
	clang -g -O0 -Wall -Wextra -pedantic -o att src/*.c
check:
	cppcheck -i.ccls-cache .
test: 
	clang -Wall -Wextra -pedantic -l cmocka -o tests test/action.c src/acton.c && ./tests ; rm tests
install:
	cp att /usr/local/bin
uninstall:
	rm /usr/local/bin/att
check-syntax:
	clang -o /dev/null -l cmocka -S ${CHK_SOURCES}
