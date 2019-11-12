#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "managers/snap.h"
#include "commands.h"

static void snap_commands_should_be_correct(void **state) {
    (void) state; /* unused */
    Commands* commands = getSnapCommands("emacs");
    assert_int_equal(0, strcmp(getCommand(commands, Clean), ""));
    assert_int_equal(0, strcmp(getCommand(commands, Install), "snap install emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, Search), "snap find emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, SearchExact), "snap find emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, Upgrade), "sudo snap refresh"));
    assert_int_equal(0, strcmp(getCommand(commands, Which), "which snap"));
}
