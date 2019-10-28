#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "requested_action.h"
#include "managers.h"
#include "action.h"
#include "apt.h"
#include "brew.h"
#include "flatpak.h"
#include "guix.h"
#include "snap.h"

struct RequestedAction {
    Managers* managers;
    enum Action action;
    char* target;
    bool exact;
    bool debug;
};

RequestedAction* requested_action_new() {
    RequestedAction* requestedAction = (RequestedAction*) malloc(sizeof(RequestedAction));

    Managers* managers = managers_new();
    setAllManagers(managers, true);
    requestedAction->managers = managers;
    requestedAction->action = InvalidAction;
    requestedAction->target = NULL;
    requestedAction->exact = false;
    requestedAction->debug = false;

    return requestedAction;
}

Managers* getRequestedActionManagers(RequestedAction* requestedAction) {
    return requestedAction->managers;
}

void setRequestedActionManagers(RequestedAction* requestedAction, Managers* managers) {
    requestedAction->managers = managers;
}

enum Action getRequestedActionAction(RequestedAction* requestedAction) {
    return requestedAction->action;
}

void setRequestedActionAction(RequestedAction* requestedAction, enum Action action) {
    requestedAction->action = action;
}

char* getRequestedActionTarget(RequestedAction* requestedAction) {
    return requestedAction->target;
}

void setRequestedActionTarget(RequestedAction* requestedAction, char* target) {
    requestedAction->target = target;
}

bool isDebug(RequestedAction* requestedAction) {
    return requestedAction->debug;
}

void enableDebug(RequestedAction* requestedAction) {
    requestedAction->debug = true;
}

bool isExactSearch(RequestedAction* requestedAction) {
    return requestedAction->exact;
}

void enableExactSearch(RequestedAction* requestedAction) {
    requestedAction->exact = true;
}

void enableManagerForRequestedAction(RequestedAction* requestedAction, char* managerName) {
    if (strcmp(managerName, APT) == 0) {
        setApt(requestedAction->managers, true);
    } else if (strcmp(managerName, BREW) == 0) {
        setBrew(requestedAction->managers, true);
    } else if (strcmp(managerName, FLATPAK) == 0) {
        setFlatpak(requestedAction->managers, true);
    } else if (strcmp(managerName, GUIX) == 0) {
        setGuix(requestedAction->managers, true);
    } else if (strcmp(managerName, SNAP) == 0) {
        setSnap(requestedAction->managers, true);
    }
}
