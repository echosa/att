#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "../include/snap.h"
#include "../include/commands.h"

static void snap_commands_should_be_correct(void **state) {
    (void) state; /* unused */
    Commands* commands = getSnapCommands("emacs");
    assert_int_equal(0, strcmp(getCleanCommand(commands), ""));
    assert_int_equal(0, strcmp(getInstallCommand(commands), "snap install emacs"));
    assert_int_equal(0, strcmp(getSearchCommand(commands), "snap find emacs"));
    assert_int_equal(0, strcmp(getSearchExactCommand(commands), "snap find emacs"));
    assert_int_equal(0, strcmp(getUpgradeCommand(commands), "sudo snap refresh"));
    assert_int_equal(0, strcmp(getWhichCommand(commands), "which snap"));
}
