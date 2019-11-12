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
    PackageManager* manager = (PackageManager*)(malloc(sizeof(PackageManager)));
    strncpy(manager->name, name, NAME_LENGTH);
    manager->commands = commands;
    manager->enabled = enabled;

    return manager;
}

bool isPackageManagerInstalled(PackageManager* manager) {
    char installedCheck[INSTALL_CHECK_LENGTH];
    snprintf(installedCheck, INSTALL_CHECK_LENGTH, "which %s > /dev/null", manager->name);

    return system(installedCheck) == 0;
}

char* getPackageManagerName(PackageManager* manager) {
    return manager->name;
}

char* getPackageManagerCommand(PackageManager* manager, enum Action action) {
    return getCommandString(manager->commands, action);
}

void setPackageManagerInstallCommand(PackageManager* manager, Commands* commands) {
    setCommand(manager->commands, Install, getCommandString(commands, Install));
}

bool isPackageManagerEnabled(PackageManager* manager) {
    return manager->enabled;
}
