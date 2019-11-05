#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdbool.h>
#include "../include/package_manager.h"
#include "../include/commands.h"

static void defining_package_manager_should_set_all_things_correctly(void **state) {
    (void) state; /* unused */
    Commands* commands = commands_new();
    setCleanCommand(commands, "clean command");
    setInstallCommand(commands, "install command");
    setSearchCommand(commands, "search command");
    setSearchExactCommand(commands, "search exact command");
    setUpgradeCommand(commands, "upgrade command");
    PackageManager* packageManager = definePackageManager("foo", commands, true);
    assert_string_equal("clean command", getPackageManagerCleanCommand(packageManager));
    assert_string_equal("install command", getPackageManagerInstallCommand(packageManager));
    assert_string_equal("search command", getPackageManagerSearchCommand(packageManager));
    assert_string_equal("search exact command", getPackageManagerSearchExactCommand(packageManager));
    assert_string_equal("upgrade command", getPackageManagerUpgradeCommand(packageManager));
    assert_true(isPackageManagerEnabled(packageManager));
    assert_string_equal("foo", getPackageManagerName(packageManager));
}

static void setting_package_manager_target_should_set_it_correctly(void **state) {
    (void) state; /* unused */
    Commands* commands = commands_new();
    setInstallCommand(commands, "install command");
    PackageManager* packageManager = definePackageManager("foo", commands, true);
    setInstallCommand(commands, "other install command");
    setPackageManagerInstallCommand(packageManager, commands);
    assert_string_equal("other install command", getPackageManagerInstallCommand(packageManager));
}

static void check_if_package_is_installed_should_work(void **state) {
    (void) state; /* unused */
    Commands* commands = commands_new();
    PackageManager* packageManager = definePackageManager("foo", commands, true);

    expect_string(__wrap_system, command, "which foo > /dev/null");
    will_return(__wrap_system, 0);
    isPackageManagerInstalled(packageManager);
}
