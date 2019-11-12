#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "../include/flatpak.h"
#include "../include/commands.h"

static void flatpak_commands_should_be_correct(void **state) {
    (void) state; /* unused */
    Commands* commands = getFlatpakCommands("emacs");
    assert_int_equal(0, strcmp(getCleanCommand(commands), "flatpak uninstall --unused"));
    assert_int_equal(0, strcmp(getInstallCommand(commands), "flatpak install emacs"));
    assert_int_equal(0, strcmp(getSearchCommand(commands), "flatpak search emacs"));
    assert_int_equal(0, strcmp(getSearchExactCommand(commands), "flatpak search emacs"));
    assert_int_equal(0, strcmp(getUpgradeCommand(commands), "flatpak update"));
    assert_int_equal(0, strcmp(getWhichCommand(commands), "which flatpak"));
}
