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
    assert_int_equal(0, strcmp(getCommandString(commands, Clean), ""));
    assert_int_equal(0, strcmp(getCommandString(commands, Install), "snap install emacs"));
    assert_int_equal(0, strcmp(getCommandString(commands, Search), "snap find emacs"));
    assert_int_equal(0, strcmp(getCommandString(commands, SearchExact), "snap find emacs"));
    assert_int_equal(0, strcmp(getCommandString(commands, Update), ""));
    assert_int_equal(0, strcmp(getCommandString(commands, Upgrade), "sudo snap refresh"));
    assert_int_equal(0, strcmp(getCommandString(commands, Which), "which snap"));
}
