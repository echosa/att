#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "../src/guix.h"
#include "../src/commands.h"

static void guix_commands_should_be_correct(void **state) {
    (void) state; /* unused */
    Commands* commands = getGuixCommands("emacs");
    assert_int_equal(0, strcmp(getCleanCommand(commands), "guix package --delete-generations; guix gc --collect-garbage; guix gc --list-dead"));
    assert_int_equal(0, strcmp(getInstallCommand(commands), "guix install emacs"));
    assert_int_equal(0, strcmp(getSearchCommand(commands), "guix package -A emacs"));
    assert_int_equal(0, strcmp(getSearchExactCommand(commands), "guix package -A ^emacs$"));
    assert_int_equal(0, strcmp(getUpgradeCommand(commands), "guix pull; guix package -u"));
}
