#include <stdbool.h>
#include <stdlib.h>
#include "../include/managers.h"

struct Managers {
    bool apt;
    bool brew;
    bool flatpak;
    bool guix;
    bool snap;
};

Managers* managers_new() {
    Managers* managers = (Managers*) malloc(sizeof(Managers));

    return managers;
}

void setAllManagers(Managers* managers, bool enabled) {
    managers->apt = enabled;
    managers->brew = enabled;
    managers->flatpak = enabled;
    managers->guix = enabled;
    managers->snap = enabled;
}

void setApt(Managers *managers, bool enabled) {
    managers->apt = enabled;
}

void setBrew(Managers *managers, bool enabled) {
    managers->brew = enabled;
}

void setFlatpak(Managers *managers, bool enabled) {
    managers->flatpak = enabled;
}

void setGuix(Managers *managers, bool enabled) {
    managers->guix = enabled;
}

void setSnap(Managers *managers, bool enabled) {
    managers->snap = enabled;
}

bool getApt(Managers *managers) {
    return managers->apt;
}

bool getBrew(Managers *managers) {
    return managers->brew;
}

bool getFlatpak(Managers *managers) {
    return managers->flatpak;
}

bool getGuix(Managers *managers) {
    return managers->guix;
}

bool getSnap(Managers *managers) {
    return managers->snap;
}
