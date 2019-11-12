#include <stdlib.h>
#include <string.h>
#include "requested_action.h"
#include "options.h"
#include "managers/apt.h"
#include "managers/brew.h"
#include "managers/flatpak.h"
#include "managers/guix.h"
#include "managers/snap.h"

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

RequestedAction* build_requested_action_from_options(int argc, char *argv[]) {
    int c;
    char *token;

    RequestedAction* requestedAction = requested_action_new();

    while (1) {
        int option_index = 0;

        c = getopt_long(argc, argv, "dehm",  long_options, &option_index);
        if (c == -1) {
            break;
        }

        switch (c) {
        case 'd':
            enableDebug(requestedAction);
            break;

        case 'e':
            enableExactSearch(requestedAction);
            break;

        case 'h':
            setRequestedActionAction(requestedAction, Help);

            return requestedAction;

        case 'm':
            setAllManagers(getRequestedActionManagers(requestedAction), false);
            while ((token = strsep(&optarg, ",")) != NULL) {
                enableManagerForRequestedAction(requestedAction, token);
            }
            break;
        }
    }

    if (optind >= argc) {
        setRequestedActionAction(requestedAction, InvalidAction);

        return requestedAction;
    }

    if (optind < argc) {
        setRequestedActionAction(requestedAction, parseAction(argv[optind++], isExactSearch(requestedAction)));
    }

    if (optind < argc) {
        setRequestedActionTarget(requestedAction, argv[optind++]);
    }

    enum Action action = getRequestedActionAction(requestedAction);
    if ((action == Search || action == SearchExact || action == Install) && getRequestedActionTarget(requestedAction) == NULL) {
        setRequestedActionAction(requestedAction, InvalidAction);
    }

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
