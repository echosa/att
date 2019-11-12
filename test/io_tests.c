#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "io.h"

static void test_usage_documentation(void **state) {
    (void) state; /* unused */
    printUsage("foo");
}
