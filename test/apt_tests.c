#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "../include/apt.h"
#include "../include/commands.h"

static void apt_commands_should_be_correct(void **state) {
    (void) state; /* unused */
    Commands* commands = getAptCommands("emacs");
    assert_int_equal(0, strcmp(getCleanCommand(commands), "sudo apt autoremove"));
    assert_int_equal(0, strcmp(getInstallCommand(commands), "sudo apt install emacs"));
    assert_int_equal(0, strcmp(getSearchCommand(commands), "apt search emacs"));
    assert_int_equal(0, strcmp(getSearchExactCommand(commands), "apt search ^emacs$"));
    assert_int_equal(0, strcmp(getUpgradeCommand(commands), "sudo apt update; sudo apt upgrade"));
}
