#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "action_tests.c"
#include "apt_tests.c"
#include "brew_tests.c"
#include "commands_tests.c"
#include "flatpak_tests.c"
#include "guix_tests.c"
#include "snap_tests.c"

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(clean_action_should_parse_correctly),
        cmocka_unit_test(install_action_should_parse_correctly),
        cmocka_unit_test(search_action_should_parse_correctly),
        cmocka_unit_test(search_exact_action_should_parse_correctly),
        cmocka_unit_test(upgrade_action_should_parse_correctly),
        cmocka_unit_test(apt_commands_should_be_correct),
        cmocka_unit_test(brew_commands_should_be_correct),
        cmocka_unit_test(flatpak_commands_should_be_correct),
        cmocka_unit_test(guix_commands_should_be_correct),
        cmocka_unit_test(snap_commands_should_be_correct),
        cmocka_unit_test(setting_and_getting_clean_command_should_be_correct),
        cmocka_unit_test(setting_and_getting_install_command_should_be_correct),
        cmocka_unit_test(setting_and_getting_search_command_should_be_correct),
        cmocka_unit_test(setting_and_getting_search_exact_command_should_be_correct),
        cmocka_unit_test(setting_and_getting_upgrade_command_should_be_correct),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
