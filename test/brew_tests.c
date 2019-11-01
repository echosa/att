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
    assert_int_equal(0, strcmp(getCleanCommand(commands), "brew cleanup"));
    assert_int_equal(0, strcmp(getInstallCommand(commands), "brew install emacs"));
    assert_int_equal(0, strcmp(getSearchCommand(commands), "brew search emacs"));
    assert_int_equal(0, strcmp(getSearchExactCommand(commands), "brew search /^emacs$/"));
    assert_int_equal(0, strcmp(getUpgradeCommand(commands), "brew update; brew upgrade"));
}
