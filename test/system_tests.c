#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "commands.h"
#include "package_manager.h"
#include "system.h"

static void check_if_package_is_installed_should_work(void **state) {
    (void) state; /* unused */
    Commands* commands = commands_new();
    PackageManager* packageManager = definePackageManager("foo", commands, true);

    expect_string(__wrap_system, command, "which foo > /dev/null");
    will_return(__wrap_system, 0);
    isPackageManagerInstalled(getPackageManagerName(packageManager));
}
