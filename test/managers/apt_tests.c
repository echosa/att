#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "../../include/managers/apt.h"
#include "../../include/commands.h"

static void apt_commands_should_be_correct(void **state) {
    (void) state; /* unused */
    Commands* commands = getAptCommands("emacs");
    assert_int_equal(0, strcmp(getCommand(commands, Clean), "sudo apt autoremove"));
    assert_int_equal(0, strcmp(getCommand(commands, Install), "sudo apt install emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, Search), "apt search emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, SearchExact), "apt search ^emacs$"));
    assert_int_equal(0, strcmp(getCommand(commands, Upgrade), "sudo apt update; sudo apt upgrade"));
    assert_int_equal(0, strcmp(getCommand(commands, Which), "which apt"));
}
