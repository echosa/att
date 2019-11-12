#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "../include/commands.h"

static void setting_and_getting_clean_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setCleanCommand(commands, command);
    assert_int_equal(0, strcmp(getCleanCommand(commands), command));
}

static void setting_and_getting_install_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setInstallCommand(commands, command);
    assert_int_equal(0, strcmp(getInstallCommand(commands), command));
}

static void setting_and_getting_search_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setSearchCommand(commands, command);
    assert_int_equal(0, strcmp(getSearchCommand(commands), command));
}

static void setting_and_getting_search_exact_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setSearchExactCommand(commands, command);
    assert_int_equal(0, strcmp(getSearchExactCommand(commands), command));
}

static void setting_and_getting_upgrade_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setUpgradeCommand(commands, command);
    assert_int_equal(0, strcmp(getUpgradeCommand(commands), command));
}

static void setting_and_getting_which_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setWhichCommand(commands, command);
    assert_int_equal(0, strcmp(getWhichCommand(commands), command));
}
