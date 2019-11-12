#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "action_tests.c"
#include "commands_tests.c"
#include "io_tests.c"
#include "managers/apt_tests.c"
#include "package_manager_tests.c"
#include "managers_tests.c"
#include "managers/brew_tests.c"
#include "managers/flatpak_tests.c"
#include "managers/guix_tests.c"
#include "managers/snap_tests.c"

int __wrap_system(const char *command) {
    check_expected(command);
    return mock();
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(clean_action_should_parse_correctly),
        cmocka_unit_test(install_action_should_parse_correctly),
        cmocka_unit_test(search_action_should_parse_correctly),
        cmocka_unit_test(search_exact_action_should_parse_correctly),
        cmocka_unit_test(update_action_should_parse_correctly),
        cmocka_unit_test(upgrade_action_should_parse_correctly),
        cmocka_unit_test(which_action_should_parse_correctly),
        cmocka_unit_test(invalid_action_should_parse_correctly),
        cmocka_unit_test(apt_commands_should_be_correct),
        cmocka_unit_test(brew_commands_should_be_correct),
        cmocka_unit_test(flatpak_commands_should_be_correct),
        cmocka_unit_test(guix_commands_should_be_correct),
        cmocka_unit_test(snap_commands_should_be_correct),
        cmocka_unit_test(setting_and_getting_clean_command_should_be_correct),
        cmocka_unit_test(setting_and_getting_install_command_should_be_correct),
        cmocka_unit_test(setting_and_getting_search_command_should_be_correct),
        cmocka_unit_test(setting_and_getting_search_exact_command_should_be_correct),
        cmocka_unit_test(setting_and_getting_update_command_should_be_correct),
        cmocka_unit_test(setting_and_getting_upgrade_command_should_be_correct),
        cmocka_unit_test(setting_and_getting_which_command_should_be_correct),
        cmocka_unit_test(setting_all_managers_should_enable_all_managers),
        cmocka_unit_test(unsetting_all_managers_should_disable_all_managers),
        cmocka_unit_test(setting_apt_manager_should_enable_it),
        cmocka_unit_test(unsetting_apt_manager_should_disable_it),
        cmocka_unit_test(setting_brew_manager_should_enable_it),
        cmocka_unit_test(unsetting_brew_manager_should_disable_it),
        cmocka_unit_test(setting_flatpak_manager_should_enable_it),
        cmocka_unit_test(unsetting_flatpak_manager_should_disable_it),
        cmocka_unit_test(setting_guix_manager_should_enable_it),
        cmocka_unit_test(unsetting_guix_manager_should_disable_it),
        cmocka_unit_test(setting_snap_manager_should_enable_it),
        cmocka_unit_test(unsetting_snap_manager_should_disable_it),
        cmocka_unit_test(defining_package_manager_should_set_all_things_correctly),
        cmocka_unit_test(setting_package_manager_target_should_set_it_correctly),
        cmocka_unit_test(check_if_package_is_installed_should_work),
        cmocka_unit_test(test_usage_documentation),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
