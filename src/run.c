#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "run.h"
#include "io.h"
#include "supported_manager.h"
#include "requested_action.h"
#include "apt.h"
#include "brew.h"
#include "flatpak.h"
#include "guix.h"
#include "snap.h"
#include "package_manager.h"

char* getCommandForAction(PackageManager* manager, RequestedAction* requestedAction) {
    switch (getRequestedActionAction(requestedAction)) {
    case Clean:
        return getPackageManagerCleanCommand(manager);
    case Install:
        return getPackageManagerInstallCommand(manager);
    case Search:
        return getPackageManagerSearchCommand(manager);
    case SearchExact:
        return getPackageManagerSearchExactCommand(manager);
    case Upgrade:
        return getPackageManagerUpgradeCommand(manager);
    default:
        return "";
    }
}

void runCommand(PackageManager* manager, RequestedAction* requestedAction) {
    printf(DIVIDER);
    printf(DIVIDER);
    printf("%s\n", getPackageManagerName(manager));
    printf(DIVIDER);

    char *command = getCommandForAction(manager, requestedAction);

    if (strcmp(command, "") == 0) {
        printf("No relevant command for %s\n", getPackageManagerName(manager));

        return;
    }

    printf("%s\n", command);
    if (!isDebug(requestedAction)) {
        system(command);
    }
}

void runCommandForAllManagers(PackageManager* managers[], RequestedAction* requestedAction) {
    for (int i = 0; i < MANAGERS_COUNT; i++) {
        if (isPackageManagerEnabled(managers[i]) && isPackageManagerInstalled(managers[i])) {
            runCommand(managers[i], requestedAction);
        }
    }
}

void runPackageSearch(PackageManager* managers[], RequestedAction* requestedAction) {
    RequestedAction* searchAction = requested_action_new();
    if (isExactSearch(requestedAction)) {
        setRequestedActionAction(searchAction, SearchExact);
    } else {
        setRequestedActionAction(searchAction, Search);
    }        
    runCommandForAllManagers(managers, searchAction);
    free(searchAction);
}

void installPackage(PackageManager* managers[], RequestedAction* requestedAction) {
    printf("Searching for package to install...\n");
    runPackageSearch(managers, requestedAction);

    printf(DIVIDER);
    printf(DIVIDER);
    printf("Which manager would you like to use? ");
    int managerIndex = promptForManager();
    if (managerIndex == -1) {
        printf("Package manager found.\n");
    }

    printf("Which package would you like to install? ");
    char packageChoice[COMMAND_LENGTH];
    scanf("%s", packageChoice);

    setRequestedActionTarget(requestedAction, packageChoice);
    PackageManager* manager = managers[managerIndex];
    Commands* commands = NULL;
    if (strcmp(getPackageManagerName(manager), APT) == 0) {
      commands = getAptCommands(packageChoice);
    } else if (strcmp(getPackageManagerName(manager), BREW) == 0) {
      commands = getBrewCommands(packageChoice);
    } else if (strcmp(getPackageManagerName(manager), FLATPAK) == 0) {
      commands = getFlatpakCommands(packageChoice);
    } else if (strcmp(getPackageManagerName(manager), GUIX) == 0) {
      commands = getGuixCommands(packageChoice);
    } else if (strcmp(getPackageManagerName(manager), SNAP) == 0) {
      commands = getSnapCommands(packageChoice);
    }
    setPackageManagerInstallCommand(manager, commands);

    printf("Installing %s from %s...\n", packageChoice, getPackageManagerName(managers[managerIndex]));
    runCommand(manager, requestedAction);
}

void executeAction(PackageManager* managers[], RequestedAction* requestedAction) {
    if (getRequestedActionAction(requestedAction) == Install) {
        installPackage(managers, requestedAction);
    } else {
        runCommandForAllManagers(managers, requestedAction);
    }

    free(getRequestedActionManagers(requestedAction));
    free(requestedAction);
    for (int i = 0; i < MANAGERS_COUNT; i++) {
        free(managers[i]);
    }
}

