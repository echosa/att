#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/package_manager.h"
#include "../include/commands.h"

struct PackageManager {
    char name[NAME_LENGTH];
    char cleanCommand[COMMAND_LENGTH];
    char installCommand[COMMAND_LENGTH];
    char searchCommand[COMMAND_LENGTH];
    char searchExactCommand[COMMAND_LENGTH];
    char upgradeCommand[COMMAND_LENGTH];
    bool enabled;
};

PackageManager* definePackageManager(const char name[], Commands* commands, bool enabled) {
    PackageManager* manager = (PackageManager*)(malloc(sizeof(PackageManager)));
    strncpy(manager->name, name, NAME_LENGTH);
    strncpy(manager->cleanCommand, getCleanCommand(commands), COMMAND_LENGTH);
    strncpy(manager->installCommand, getInstallCommand(commands), COMMAND_LENGTH);
    strncpy(manager->searchCommand, getSearchCommand(commands), COMMAND_LENGTH);
    strncpy(manager->searchExactCommand, getSearchExactCommand(commands), COMMAND_LENGTH);
    strncpy(manager->upgradeCommand, getUpgradeCommand(commands), COMMAND_LENGTH);
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

char* getPackageManagerCleanCommand(PackageManager* manager) {
    return manager->cleanCommand;
}

char* getPackageManagerInstallCommand(PackageManager* manager) {
    return manager->installCommand;
}

char* getPackageManagerSearchCommand(PackageManager* manager) {
    return manager->searchCommand;
}

char* getPackageManagerSearchExactCommand(PackageManager* manager) {
    return manager->searchExactCommand;
}

char* getPackageManagerUpgradeCommand(PackageManager* manager) {
    return manager->upgradeCommand;
}

void setPackageManagerInstallCommand(PackageManager* manager, Commands* commands) {
    strncpy(manager->installCommand, getInstallCommand(commands), COMMAND_LENGTH);
}

bool isPackageManagerEnabled(PackageManager* manager) {
    return manager->enabled;
}
