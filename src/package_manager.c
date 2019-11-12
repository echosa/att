#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "package_manager.h"
#include "commands.h"

struct PackageManager {
    char name[NAME_LENGTH];
    char cleanCommand[COMMAND_LENGTH];
    char installCommand[COMMAND_LENGTH];
    char searchCommand[COMMAND_LENGTH];
    char searchExactCommand[COMMAND_LENGTH];
    char upgradeCommand[COMMAND_LENGTH];
    char whichCommand[COMMAND_LENGTH];
    bool enabled;
};

PackageManager* definePackageManager(const char name[], Commands* commands, bool enabled) {
    PackageManager* manager = (PackageManager*)(malloc(sizeof(PackageManager)));
    strncpy(manager->name, name, NAME_LENGTH);
    strncpy(manager->cleanCommand, getCommand(commands, Clean), COMMAND_LENGTH);
    strncpy(manager->installCommand, getCommand(commands, Install), COMMAND_LENGTH);
    strncpy(manager->searchCommand, getCommand(commands, Search), COMMAND_LENGTH);
    strncpy(manager->searchExactCommand, getCommand(commands, SearchExact), COMMAND_LENGTH);
    strncpy(manager->upgradeCommand, getCommand(commands, Upgrade), COMMAND_LENGTH);
    strncpy(manager->whichCommand, getCommand(commands, Which), COMMAND_LENGTH);
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
    if (action == Clean) {
        return manager->cleanCommand;
    } else if (action == Install) {
        return manager->installCommand;
    } else if (action == Search) {
        return manager->searchCommand;
    } else if (action == SearchExact) {
        return manager->searchExactCommand;
    } else if (action == Upgrade) {
        return manager->upgradeCommand;
    } else if (action == Which) {
        return manager->whichCommand;
    }

    return "";
}

void setPackageManagerInstallCommand(PackageManager* manager, Commands* commands) {
    strncpy(manager->installCommand, getCommand(commands, Install), COMMAND_LENGTH);
}

bool isPackageManagerEnabled(PackageManager* manager) {
    return manager->enabled;
}
