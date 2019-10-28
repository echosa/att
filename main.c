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
#include "run.h"

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
