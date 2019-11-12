#include <stdlib.h>
#include "io.h"
#include "requested_action.h"
#include "package_manager.h"
#include "supported_manager.h"
#include "run.h"

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
