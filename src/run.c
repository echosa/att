#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "run.h"
#include "io.h"
#include "supported_managers.h"
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

void runCommandString(PackageManager* packageManager, char* command, bool isDebug) {
    printf(DIVIDER);
    printf(DIVIDER);
    printf("%s\n", getPackageManagerName(packageManager));
    printf(DIVIDER);

    if (strcmp(command, "") == 0) {
        printf("No relevant command for %s\n", getPackageManagerName(packageManager));

        return;
    }

    printf("%s\n", command);
    if (!isDebug) {
        system(command);
    }
}

void runRequestedActionCommand(PackageManager* packageManager, RequestedAction* requestedAction) {
    char *command = getCommandForAction(packageManager, requestedAction);
    runCommandString(packageManager, command, isDebug(requestedAction));
}

void runCommandForAllManagers(PackageManager* packageManagers[], RequestedAction* requestedAction) {
    for (int i = 0; i < MANAGERS_COUNT; i++) {
        if (isPackageManagerEnabled(packageManagers[i]) && isPackageManagerInstalled(packageManagers[i])) {
            runRequestedActionCommand(packageManagers[i], requestedAction);
        }
    }
}

void runPackageSearch(PackageManager* packageManagers[], RequestedAction* requestedAction) {
    RequestedAction* searchAction = requested_action_new();
    if (isExactSearch(requestedAction)) {
        setRequestedActionAction(searchAction, SearchExact);
    } else {
        setRequestedActionAction(searchAction, Search);
    }
    runCommandForAllManagers(packageManagers, searchAction);
    free(searchAction);
}

void installPackage(PackageManager* packageManagers[], RequestedAction* requestedAction) {
    printf("Searching for package to install...\n");
    runPackageSearch(packageManagers, requestedAction);

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
    PackageManager* packageManager = packageManagers[managerIndex];
    Commands* commands = NULL;
    if (strcmp(getPackageManagerName(packageManager), APT) == 0) {
      commands = getAptCommands(packageChoice);
    } else if (strcmp(getPackageManagerName(packageManager), BREW) == 0) {
      commands = getBrewCommands(packageChoice);
    } else if (strcmp(getPackageManagerName(packageManager), FLATPAK) == 0) {
      commands = getFlatpakCommands(packageChoice);
    } else if (strcmp(getPackageManagerName(packageManager), GUIX) == 0) {
      commands = getGuixCommands(packageChoice);
    } else if (strcmp(getPackageManagerName(packageManager), SNAP) == 0) {
      commands = getSnapCommands(packageChoice);
    } else {
        printf("Invalid package manager");

        return;
    }
    setPackageManagerInstallCommand(packageManager, commands);

    printf("Installing %s from %s...\n", packageChoice, getPackageManagerName(packageManagers[managerIndex]));
    runRequestedActionCommand(packageManager, requestedAction);
}

void executeAction(PackageManager* packageManagers[], RequestedAction* requestedAction) {
    if (getRequestedActionAction(requestedAction) == Install) {
        installPackage(packageManagers, requestedAction);
    } else {
        runCommandForAllManagers(packageManagers, requestedAction);
    }

    free(getRequestedActionManagers(requestedAction));
    free(requestedAction);
    for (int i = 0; i < MANAGERS_COUNT; i++) {
        free(packageManagers[i]);
    }
}

