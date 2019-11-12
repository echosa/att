#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "../../include/managers/flatpak.h"
#include "../../include/commands.h"

static void flatpak_commands_should_be_correct(void **state) {
    (void) state; /* unused */
    Commands* commands = getFlatpakCommands("emacs");
    assert_int_equal(0, strcmp(getCommand(commands, Clean), "flatpak uninstall --unused"));
    assert_int_equal(0, strcmp(getCommand(commands, Install), "flatpak install emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, Search), "flatpak search emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, SearchExact), "flatpak search emacs"));
    assert_int_equal(0, strcmp(getCommand(commands, Upgrade), "flatpak update"));
    assert_int_equal(0, strcmp(getCommand(commands, Which), "which flatpak"));
}
