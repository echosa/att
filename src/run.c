#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "run.h"
#include "io.h"
#include "supported_manager.h"
#include "requested_action.h"
#include "managers/apt.h"
#include "managers/brew.h"
#include "managers/flatpak.h"
#include "managers/guix.h"
#include "managers/snap.h"
#include "package_manager.h"

char* getCommandForAction(PackageManager* packageManager, RequestedAction* requestedAction) {
    Commands* commands = getPackageManagerCommands(packageManager);
    return getCommandString(commands, getRequestedActionAction(requestedAction));
}

void runCommandString(PackageManager* manager, char* command, bool isDebug) {
    printf(DIVIDER);
    printf(DIVIDER);
    printf("%s\n", getPackageManagerName(manager));
    printf(DIVIDER);

    if (strcmp(command, "") == 0) {
        printf("No relevant command for %s\n", getPackageManagerName(manager));

        return;
    }

    printf("%s\n", command);
    if (!isDebug) {
        system(command);
    }
}

void runRequestedActionCommand(PackageManager* manager, RequestedAction* requestedAction) {
    char *command = getCommandForAction(manager, requestedAction);
    runCommandString(manager, command, isDebug(requestedAction));
}

void runCommandForAllManagers(PackageManager* managers[], RequestedAction* requestedAction) {
    for (int i = 0; i < MANAGERS_COUNT; i++) {
        if (isPackageManagerEnabled(managers[i]) && isPackageManagerInstalled(managers[i])) {
            runRequestedActionCommand(managers[i], requestedAction);
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
    } else {
        printf("Invalid package manager");

        return;
    }
    setPackageManagerInstallCommand(manager, commands);

    printf("Installing %s from %s...\n", packageChoice, getPackageManagerName(managers[managerIndex]));
    runRequestedActionCommand(manager, requestedAction);
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

