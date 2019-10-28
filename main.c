#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "action.h"
#include "managers.h"
#include "commands.h"
#include "apt.h"
#include "brew.h"
#include "flatpak.h"
#include "guix.h"
#include "snap.h"
#include "io.h"
#include "package_manager.h"
#include "requested_action.h"
#include "supported_manager.h"


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

int promptForManager() {
    char managerChoice[COMMAND_LENGTH];
    scanf("%s", managerChoice);

    return getManagerIndex(managerChoice);
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

    printf("Installing %s from %s...\n", packageChoice, getPackageManagerName(managers[managerIndex]));
    runCommand(managers[managerIndex], requestedAction);
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

/*********
* Package Managers
*********/
PackageManager* apt(RequestedAction* requestedAction) {
    return definePackageManager(APT, getAptCommands(getRequestedActionTarget(requestedAction)), getApt(getRequestedActionManagers(requestedAction)));
}

PackageManager* brew(RequestedAction* requestedAction) {
    return definePackageManager(BREW, getBrewCommands(getRequestedActionTarget(requestedAction)), getBrew(getRequestedActionManagers(requestedAction)));
}

PackageManager* flatpak(RequestedAction* requestedAction) {
    return definePackageManager(FLATPAK, getFlatpakCommands(getRequestedActionTarget(requestedAction)), getFlatpak(getRequestedActionManagers(requestedAction)));
}

PackageManager* guix(RequestedAction* requestedAction) {
    return definePackageManager(GUIX, getGuixCommands(getRequestedActionTarget(requestedAction)), getGuix(getRequestedActionManagers(requestedAction)));
}

PackageManager* snap(RequestedAction* requestedAction) {
    return definePackageManager(SNAP, getSnapCommands(getRequestedActionTarget(requestedAction)), getSnap(getRequestedActionManagers(requestedAction)));
}

/*********
* Main
*********/
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);

        return EXIT_FAILURE;
    }

    RequestedAction* requestedAction = build_requested_action_from_options(argc, argv);

    if (getRequestedActionAction(requestedAction) == InvalidAction) {
        printUsage(argv[0]);

        return EXIT_FAILURE;
    }

    if (getRequestedActionAction(requestedAction) == Help) {
        printUsage(argv[0]);

        return EXIT_SUCCESS;
    }

    PackageManager* managers[] = {
        apt(requestedAction),
        brew(requestedAction),
        flatpak(requestedAction),
        guix(requestedAction),
        snap(requestedAction)
    };
    executeAction(managers, requestedAction);

    return EXIT_SUCCESS;
}
