#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "system.h"

bool isPackageManagerInstalled(char* name) {
    char installedCheck[INSTALL_CHECK_LENGTH];
    snprintf(installedCheck, INSTALL_CHECK_LENGTH, "which %s > /dev/null", name);

    return system(installedCheck) == 0;
}
