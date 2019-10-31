#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdbool.h>
#include "../src/managers.h"

static void setting_all_managers_should_enable_all_managers(void **state) {
    (void) state; /* unused */
    Managers* managers = managers_new();
    setAllManagers(managers, true);
    assert_true(getApt(managers));
    assert_true(getBrew(managers));
    assert_true(getFlatpak(managers));
    assert_true(getGuix(managers));
    assert_true(getSnap(managers));
}

static void unsetting_all_managers_should_disable_all_managers(void **state) {
    (void) state; /* unused */
    Managers* managers = managers_new();
    setAllManagers(managers, false);
    assert_false(getApt(managers));
    assert_false(getBrew(managers));
    assert_false(getFlatpak(managers));
    assert_false(getGuix(managers));
    assert_false(getSnap(managers));
}

static void setting_apt_manager_should_enable_it(void **state) {
    (void)state; /* unused */
    Managers *managers = managers_new();
    setApt(managers, true);
    assert_true(getApt(managers));
}

static void unsetting_apt_manager_should_disable_it(void **state) {
    (void)state; /* unused */
    Managers *managers = managers_new();
    setApt(managers, false);
    assert_false(getApt(managers));
}

static void setting_brew_manager_should_enable_it(void **state) {
    (void)state; /* unused */
    Managers *managers = managers_new();
    setBrew(managers, true);
    assert_true(getBrew(managers));
}

static void unsetting_brew_manager_should_disable_it(void **state) {
    (void)state; /* unused */
    Managers *managers = managers_new();
    setBrew(managers, false);
    assert_false(getBrew(managers));
}

static void setting_flatpak_manager_should_enable_it(void **state) {
    (void)state; /* unused */
    Managers *managers = managers_new();
    setFlatpak(managers, true);
    assert_true(getFlatpak(managers));
}

static void unsetting_flatpak_manager_should_disable_it(void **state) {
    (void)state; /* unused */
    Managers *managers = managers_new();
    setFlatpak(managers, false);
    assert_false(getFlatpak(managers));
}

static void setting_guix_manager_should_enable_it(void **state) {
    (void)state; /* unused */
    Managers *managers = managers_new();
    setGuix(managers, true);
    assert_true(getGuix(managers));
}

static void unsetting_guix_manager_should_disable_it(void **state) {
    (void)state; /* unused */
    Managers *managers = managers_new();
    setGuix(managers, false);
    assert_false(getGuix(managers));
}

static void setting_snap_manager_should_enable_it(void **state) {
    (void)state; /* unused */
    Managers *managers = managers_new();
    setSnap(managers, true);
    assert_true(getSnap(managers));
}

static void unsetting_snap_manager_should_disable_it(void **state) {
    (void)state; /* unused */
    Managers *managers = managers_new();
    setSnap(managers, false);
    assert_false(getSnap(managers));
}

