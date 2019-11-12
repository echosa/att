#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "managers/flatpak.h"
#include "commands.h"

static void flatpak_commands_should_be_correct(void **state) {
    (void) state; /* unused */
    Commands* commands = getFlatpakCommands("emacs");
    assert_int_equal(0, strcmp(getCommandString(commands, Clean), "flatpak uninstall --unused"));
    assert_int_equal(0, strcmp(getCommandString(commands, Install), "flatpak install emacs"));
    assert_int_equal(0, strcmp(getCommandString(commands, Search), "flatpak search emacs"));
    assert_int_equal(0, strcmp(getCommandString(commands, SearchExact), "flatpak search emacs"));
    assert_int_equal(0, strcmp(getCommandString(commands, Update), ""));
    assert_int_equal(0, strcmp(getCommandString(commands, Upgrade), "flatpak update"));
    assert_int_equal(0, strcmp(getCommandString(commands, Which), "which flatpak"));
}
