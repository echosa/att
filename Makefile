CLANG=clang -Wall -Wextra -pedantic -Iinclude
CLANG_TESTS=$(CLANG) -l cmocka -Wl,--wrap=system
CLANG_COVERAGE=$(CLANG_TESTS) --coverage
CLANG_CHECK_SYNTAX=clang -l cmocka -Iinclude -o /dev/null -S ${CHK_SOURCES}

att: src/*.c
	find src -type f -iname "*.c"|xargs $(CLANG) -o bin/att
debug: src/*.c
	find src -type f -iname "*.c"|xargs $(CLANG) -o bin/att -g -O0 
check:
	cppcheck -i.ccls-cache .
test: 
	find src -type f \( -iname "*.c" ! -iname "main.c" \)|xargs $(CLANG_TESTS) -o test/tests test/tests.c \
	&& test/tests \
	&& rm test/tests
coverage: 
	find src -type f \( -iname "*.c" ! -iname "main.c" \)|xargs $(CLANG_COVERAGE) -o test/tests test/tests.c \
	&& test/tests \
	&& rm test/tests \
	&& llvm-cov-9 gcov -f -b *.gcda \
	&& lcov --directory . --base-directory . --gcov-tool ./llvm-gcov.sh --capture -o cov.info \
	&& genhtml cov.info -o coverage \
	&& rm *.gcno *.gcda cov.info
install:
	cp bin/att /usr/local/bin
uninstall:
	rm /usr/local/bin/att
check-syntax:
	$(CLANG_CHECK_SYNTAX)
.PHONY: test coverage
