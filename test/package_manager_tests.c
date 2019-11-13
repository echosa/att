#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdbool.h>
#include "package_manager.h"
#include "commands.h"

static void defining_package_manager_should_set_all_things_correctly(void **state) {
    (void) state; /* unused */
    Commands* commands = commands_new();
    setCommandString(commands, Clean, "clean command");
    setCommandString(commands, Install, "install command");
    setCommandString(commands, Search, "search command");
    setCommandString(commands, SearchExact, "search exact command");
    setCommandString(commands, Upgrade, "upgrade command");
    setCommandString(commands, Which, "which command");
    PackageManager* packageManager = definePackageManager("foo", commands, true);
    commands = getPackageManagerCommands(packageManager);
    assert_string_equal("clean command", getCommandString(commands, Clean));
    assert_string_equal("install command", getCommandString(commands, Install));
    assert_string_equal("search command", getCommandString(commands, Search));
    assert_string_equal("search exact command", getCommandString(commands, SearchExact));
    assert_string_equal("upgrade command", getCommandString(commands, Upgrade));
    assert_string_equal("which command", getCommandString(commands, Which));
    assert_true(isPackageManagerEnabled(packageManager));
    assert_string_equal("foo", getPackageManagerName(packageManager));
}

static void setting_package_manager_target_should_set_it_correctly(void **state) {
    (void) state; /* unused */
    Commands* commands = commands_new();
    setCommandString(commands, Install, "install command");
    PackageManager* packageManager = definePackageManager("foo", commands, true);
    setCommandString(commands, Install, "other install command");
    setPackageManagerInstallCommand(packageManager, commands);
    assert_string_equal("other install command", getCommandString(getPackageManagerCommands(packageManager), Install));
}
