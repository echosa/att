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
    setCommand(commands, Clean, "clean command");
    setCommand(commands, Install, "install command");
    setCommand(commands, Search, "search command");
    setCommand(commands, SearchExact, "search exact command");
    setCommand(commands, Upgrade, "upgrade command");
    setCommand(commands, Which, "which command");
    PackageManager* packageManager = definePackageManager("foo", commands, true);
    assert_string_equal("clean command", getPackageManagerCommand(packageManager, Clean));
    assert_string_equal("install command", getPackageManagerCommand(packageManager, Install));
    assert_string_equal("search command", getPackageManagerCommand(packageManager, Search));
    assert_string_equal("search exact command", getPackageManagerCommand(packageManager, SearchExact));
    assert_string_equal("upgrade command", getPackageManagerCommand(packageManager, Upgrade));
    assert_string_equal("which command", getPackageManagerCommand(packageManager, Which));
    assert_true(isPackageManagerEnabled(packageManager));
    assert_string_equal("foo", getPackageManagerName(packageManager));
}

static void setting_package_manager_target_should_set_it_correctly(void **state) {
    (void) state; /* unused */
    Commands* commands = commands_new();
    setCommand(commands, Install, "install command");
    PackageManager* packageManager = definePackageManager("foo", commands, true);
    setCommand(commands, Install, "other install command");
    setPackageManagerInstallCommand(packageManager, commands);
    assert_string_equal("other install command", getPackageManagerCommand(packageManager, Install));
}

static void check_if_package_is_installed_should_work(void **state) {
    (void) state; /* unused */
    Commands* commands = commands_new();
    PackageManager* packageManager = definePackageManager("foo", commands, true);

    expect_string(__wrap_system, command, "which foo > /dev/null");
    will_return(__wrap_system, 0);
    isPackageManagerInstalled(packageManager);
}
