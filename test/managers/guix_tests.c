#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "managers/guix.h"
#include "commands.h"

static void guix_commands_should_be_correct(void **state) {
    (void) state; /* unused */
    Commands* commands = getGuixCommands("emacs");
    assert_int_equal(0, strcmp(getCommand(commands, Clean), "guix package --delete-generations; guix gc --collect-garbage; guix gc --list-dead"));
    assert_int_equal(0, strcmp(getCommand(commands, Install), "guix install emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, Search), "guix package -A emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, SearchExact), "guix package -A ^emacs$"));
    assert_int_equal(0, strcmp(getCommand(commands, Upgrade), "guix pull; guix package -u"));
    assert_int_equal(0, strcmp(getCommand(commands, Which), "which guix"));
}
