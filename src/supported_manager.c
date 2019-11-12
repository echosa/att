#include <string.h>
#include "supported_manager.h"
#include "managers/apt.h"
#include "managers/brew.h"
#include "managers/flatpak.h"
#include "managers/guix.h"
#include "managers/snap.h"

enum SupportedManager getManagerIndex(char* managerName) {
    if (strcmp(managerName, APT) == 0) {
        return Apt;
    } else if (strcmp(managerName, BREW) == 0) {
        return Brew;
    } else if (strcmp(managerName, FLATPAK) == 0) {
        return Flatpak;
    } else if (strcmp(managerName, GUIX) == 0) {
        return Guix;
    } else if (strcmp(managerName, SNAP) == 0) {
        return Snap;
    } else {
        return InvalidManager;
    }
}

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

