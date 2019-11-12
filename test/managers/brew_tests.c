#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "managers/brew.h"
#include "commands.h"

static void brew_commands_should_be_correct(void **state) {
    (void) state; /* unused */
    Commands* commands = getBrewCommands("emacs");
    assert_int_equal(0, strcmp(getCommandString(commands, Clean), "brew cleanup"));
    assert_int_equal(0, strcmp(getCommandString(commands, Install), "brew install emacs"));
    assert_int_equal(0, strcmp(getCommandString(commands, Search), "brew search emacs"));
    assert_int_equal(0, strcmp(getCommandString(commands, SearchExact), "brew search /^emacs$/"));
    assert_int_equal(0, strcmp(getCommandString(commands, Update), "brew update"));
    assert_int_equal(0, strcmp(getCommandString(commands, Upgrade), "brew update; brew upgrade"));
    assert_int_equal(0, strcmp(getCommandString(commands, Which), "which brew"));
}
