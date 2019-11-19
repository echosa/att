check-syntax:
	clang -Wall -Wextra -pedantic -I include -l cmocka -o /dev/null -S ${CHK_SOURCES}
