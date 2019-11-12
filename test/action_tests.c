#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../include/action.h"

static void clean_action_should_parse_correctly(void **state) {
    (void) state; /* unused */
    enum Action action = parseAction((char*) CLEAN_ACTION, false);
    assert_int_equal(action, Clean);
}

static void install_action_should_parse_correctly(void **state) {
    (void) state; /* unused */
    enum Action action = parseAction((char*) INSTALL_ACTION, false);
    assert_int_equal(action, Install);
}

static void search_action_should_parse_correctly(void **state) {
    (void) state; /* unused */
    enum Action action = parseAction((char*) SEARCH_ACTION, false);
    assert_int_equal(action, Search);
}

static void search_exact_action_should_parse_correctly(void **state) {
    (void) state; /* unused */
    enum Action action = parseAction((char*) SEARCH_ACTION, true);
    assert_int_equal(action, SearchExact);
}

static void upgrade_action_should_parse_correctly(void **state) {
    (void) state; /* unused */
    enum Action action = parseAction((char*) UPGRADE_ACTION, false);
    assert_int_equal(action, Upgrade);
}

static void which_action_should_parse_correctly(void **state) {
    (void) state; /* unused */
    enum Action action = parseAction((char*) WHICH_ACTION, false);
    assert_int_equal(action, Which);
}

static void invalid_action_should_parse_correctly(void **state) {
    (void) state; /* unused */
    enum Action action = parseAction("invalid action", false);
    assert_int_equal(action, InvalidAction);
}
