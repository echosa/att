#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "commands.h"

static void setting_and_getting_clean_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setCommandString(commands, Clean, command);
    assert_int_equal(0, strcmp(getCommandString(commands, Clean), command));
}

static void setting_and_getting_install_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setCommandString(commands, Install, command);
    assert_int_equal(0, strcmp(getCommandString(commands, Install), command));
}

static void setting_and_getting_search_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setCommandString(commands, Search, command);
    assert_int_equal(0, strcmp(getCommandString(commands, Search), command));
}

static void setting_and_getting_search_exact_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setCommandString(commands, SearchExact, command);
    assert_int_equal(0, strcmp(getCommandString(commands, SearchExact), command));
}

static void setting_and_getting_upgrade_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setCommandString(commands, Upgrade, command);
    assert_int_equal(0, strcmp(getCommandString(commands, Upgrade), command));
}

static void setting_and_getting_which_command_should_be_correct(void **state) {
    (void) state; /* unused */
    char command[] = "foobar";
    Commands* commands = commands_new();
    setCommandString(commands, Which, command);
    assert_int_equal(0, strcmp(getCommandString(commands, Which), command));
}
