#include <string.h>
#include "supported_manager.h"
#include "apt.h"
#include "brew.h"
#include "flatpak.h"
#include "guix.h"
#include "snap.h"

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

