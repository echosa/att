#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "package_manager.h"
#include "commands.h"

struct PackageManager {
    char name[NAME_LENGTH];
    Commands* commands;
    bool enabled;
};

PackageManager* definePackageManager(const char name[], Commands* commands, bool enabled) {
    PackageManager* packageManager = (PackageManager*)(malloc(sizeof(PackageManager)));
    strncpy(packageManager->name, name, NAME_LENGTH);
    packageManager->commands = commands;
    packageManager->enabled = enabled;

    return packageManager;
}

bool isPackageManagerInstalled(PackageManager* packageManager) {
    char installedCheck[INSTALL_CHECK_LENGTH];
    snprintf(installedCheck, INSTALL_CHECK_LENGTH, "which %s > /dev/null", packageManager->name);

    return system(installedCheck) == 0;
}

char* getPackageManagerName(PackageManager* packageManager) {
    return packageManager->name;
}

Commands* getPackageManagerCommands(PackageManager* packageManager) {
    return packageManager->commands;
}

void setPackageManagerInstallCommand(PackageManager* packageManager, Commands* commands) {
    setCommandString(packageManager->commands, Install, getCommandString(commands, Install));
}

bool isPackageManagerEnabled(PackageManager* packageManager) {
    return packageManager->enabled;
}
