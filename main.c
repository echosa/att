#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "managers.h"
#include "commands.h"
#include "apt.h"
#include "brew.h"
#include "flatpak.h"
#include "guix.h"
#include "snap.h"
#include "io.h"
#include "package_manager.h"

static const char DEBUG_OPTION[] = "debug";
static const char EXACT_SEARCH_OPTION[] = "exact";
static const char HELP_OPTION[] = "help";
static const char MANAGERS_OPTION[] = "managers";

static struct option long_options[] = {
    { DEBUG_OPTION, no_argument, NULL, 'd' },
    { EXACT_SEARCH_OPTION, no_argument, NULL, 'e' },
    { HELP_OPTION, no_argument, NULL, 'h' },
    { MANAGERS_OPTION, required_argument, NULL, 'm' },
    { NULL, 0, NULL, 0 }
};

enum Manager { Apt, Brew, Flatpak, Guix, Snap, InvalidManager };
static const int MANAGERS_COUNT = 5;

/*********
* Structs
*********/
typedef struct ParsedAction {
    Managers* managers;
    enum Action action;
    char* target;
    bool exact;
    bool debug;
} ParsedAction;

/*********
* Functions
*********/
void setManager(ParsedAction* parsedAction, char* managerName) {
    if (strcmp(managerName, APT) == 0) {
        setApt(parsedAction->managers, true);
    } else if (strcmp(managerName, BREW) == 0) {
        setBrew(parsedAction->managers, true);
    } else if (strcmp(managerName, FLATPAK) == 0) {
        setFlatpak(parsedAction->managers, true);
    } else if (strcmp(managerName, GUIX) == 0) {
        setGuix(parsedAction->managers, true);
    } else if (strcmp(managerName, SNAP) == 0) {
        setSnap(parsedAction->managers, true);
    }
}

void setParsedActionDefaults(ParsedAction* parsedAction) {
    Managers* managers = managers_new();
    setAllManagers(managers, true);
    parsedAction->managers = managers;
    parsedAction->action = InvalidAction;
    parsedAction->target = NULL;
    parsedAction->exact = false;
    parsedAction->debug = false;
}

ParsedAction* parseOptions(int argc, char *argv[]) {
    int c;
    char *token;

    ParsedAction* parsedAction = (ParsedAction*)(malloc(sizeof(ParsedAction)));
    setParsedActionDefaults(parsedAction);

    while (1) {
        int option_index = 0;

        c = getopt_long(argc, argv, "dehm",  long_options, &option_index);
        if (c == -1) {
            break;
        }

        switch (c) {
        case 'd':
            parsedAction->debug = true;
            break;

        case 'e':
            parsedAction->exact = true;
            break;

        case 'h':
            parsedAction->action = Help;

            return parsedAction;

        case 'm':
            setAllManagers(parsedAction->managers, false);
            while ((token = strsep(&optarg, ",")) != NULL) {
                setManager(parsedAction, token);
            }
            break;
        }
    }

    if (optind >= argc) {
        parsedAction->action = InvalidAction;

        return parsedAction;
    }

    if (optind < argc) {
        parsedAction->action = parseAction(argv[optind++], parsedAction->exact);
    }

    if (optind < argc) {
        parsedAction->target = argv[optind++];
    }

    if ((parsedAction->action == Search || parsedAction->action == SearchExact || parsedAction->action == Install) && parsedAction->target == NULL) {
        parsedAction->action = InvalidAction;
    }

    return parsedAction;
}

char* getCommandForAction(PackageManager* manager, ParsedAction* parsedAction) {
    switch (parsedAction->action) {
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

void runCommand(PackageManager* manager, ParsedAction* parsedAction) {
    printf(DIVIDER);
    printf(DIVIDER);
    printf("%s\n", getPackageManagerName(manager));
    printf(DIVIDER);

    char *command = getCommandForAction(manager, parsedAction);

    if (strcmp(command, "") == 0) {
        printf("No relevant command for %s\n", getPackageManagerName(manager));

        return;
    }

    printf("%s\n", command);
    if (!parsedAction->debug) {
        system(command);
    }
}

void runCommandForAllManagers(PackageManager* managers[], ParsedAction* parsedAction) {
    for (int i = 0; i < MANAGERS_COUNT; i++) {
        if (isPackageManagerEnabled(managers[i]) && isPackageManagerInstalled(managers[i])) {
            runCommand(managers[i], parsedAction);
        }
    }
}

void runPackageSearch(PackageManager* managers[], ParsedAction* parsedAction) {
    ParsedAction* searchAction = (ParsedAction*)(malloc(sizeof(ParsedAction)));
    if (parsedAction->exact) {
        searchAction->action = SearchExact;
    } else {
        searchAction->action = Search;
    }        
    runCommandForAllManagers(managers, searchAction);
    free(searchAction);
}

enum Manager getManagerIndex(char* managerName) {
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

int promptForManager() {
    char managerChoice[COMMAND_LENGTH];
    scanf("%s", managerChoice);

    return getManagerIndex(managerChoice);
}

void installPackage(PackageManager* managers[], ParsedAction* parsedAction) {
    printf("Searching for package to install...\n");
    runPackageSearch(managers, parsedAction);

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
    runCommand(managers[managerIndex], parsedAction);
}

void executeAction(PackageManager* managers[], ParsedAction* parsedAction) {
    if (parsedAction->action == Install) {
        installPackage(managers, parsedAction);
    } else {
        runCommandForAllManagers(managers, parsedAction);
    }

    free(parsedAction->managers);
    free(parsedAction);
    for (int i = 0; i < MANAGERS_COUNT; i++) {
        free(managers[i]);
    }
}

/*********
* Package Managers
*********/
PackageManager* apt(ParsedAction* parsedAction) {
    return definePackageManager(APT, getAptCommands(parsedAction->target), getApt(parsedAction->managers));
}

PackageManager* brew(ParsedAction* parsedAction) {
    return definePackageManager(BREW, getBrewCommands(parsedAction->target), getBrew(parsedAction->managers));
}

PackageManager* flatpak(ParsedAction* parsedAction) {
    return definePackageManager(FLATPAK, getFlatpakCommands(parsedAction->target), getFlatpak(parsedAction->managers));
}

PackageManager* guix(ParsedAction* parsedAction) {
    return definePackageManager(GUIX, getGuixCommands(parsedAction->target), getGuix(parsedAction->managers));
}

PackageManager* snap(ParsedAction* parsedAction) {
    return definePackageManager(SNAP, getSnapCommands(parsedAction->target), getSnap(parsedAction->managers));
}

/*********
* Main
*********/
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);

        return EXIT_FAILURE;
    }

    ParsedAction* parsedAction = parseOptions(argc, argv);

    if (parsedAction->action == InvalidAction) {
        printUsage(argv[0]);

        return EXIT_FAILURE;
    }

    if (parsedAction->action == Help) {
        printUsage(argv[0]);

        return EXIT_SUCCESS;
    }

    PackageManager* managers[] = {
        apt(parsedAction),
        brew(parsedAction),
        flatpak(parsedAction),
        guix(parsedAction),
        snap(parsedAction)
    };
    executeAction(managers, parsedAction);

    return EXIT_SUCCESS;
}
