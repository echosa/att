att: src/*.c
	clang -Wall -Wextra -pedantic -o att src/*.c
debug: src/*.c
	clang -g -O0 -Wall -Wextra -pedantic -o att src/*.c
check:
	cppcheck -i.ccls-cache .
test: 
	find src -type f \( -iname "*.c" ! -iname "main.c" \)|xargs clang -Wall -Wextra -pedantic -l cmocka -o tests test/tests.c && ./tests ; rm tests
install:
	cp att /usr/local/bin
uninstall:
	rm /usr/local/bin/att
check-syntax:
	clang -o /dev/null -l cmocka -S ${CHK_SOURCES}
.PHONY: test
