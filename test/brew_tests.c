#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "../include/brew.h"
#include "../include/commands.h"

static void brew_commands_should_be_correct(void **state) {
    (void) state; /* unused */
    Commands* commands = getBrewCommands("emacs");
    assert_int_equal(0, strcmp(getCommand(commands, Clean), "brew cleanup"));
    assert_int_equal(0, strcmp(getCommand(commands, Install), "brew install emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, Search), "brew search emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, SearchExact), "brew search /^emacs$/"));
    assert_int_equal(0, strcmp(getCommand(commands, Upgrade), "brew update; brew upgrade"));
    assert_int_equal(0, strcmp(getCommand(commands, Which), "which brew"));
}
