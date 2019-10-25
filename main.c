#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 10
#define COMMAND_LENGTH 100
#define INSTALL_CHECK_LENGTH 50

enum Action { Clean, Install, Search, SearchExact, Upgrade, Help, InvalidAction };
static const char CLEAN_ACTION[] = "clean";
static const char INSTALL_ACTION[] = "install";
static const char SEARCH_ACTION[] = "search";
static const char UPGRADE_ACTION[] = "upgrade";

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

static const char DIVIDER[] = "####################\n";

enum Manager { Apt, Brew, Flatpak, Guix, Snap, InvalidManager };
static const int MANAGERS_COUNT = 5;
static const char APT[] = "apt";
static const char BREW[] = "brew";
static const char FLATPAK[] = "flatpak";
static const char GUIX[] = "guix";
static const char SNAP[] = "snap";

/*********
* Structs
*********/
struct Managers {
    bool apt;
    bool brew;
    bool flatpak;
    bool guix;
    bool snap;
};

struct ParsedAction {
    struct Managers* managers;
    enum Action action;
    char* target;
    bool exact;
    bool debug;
};

struct PackageManager {
    char name[NAME_LENGTH];
    char cleanCommand[COMMAND_LENGTH];
    char installCommand[COMMAND_LENGTH];
    char searchCommand[COMMAND_LENGTH];
    char searchExactCommand[COMMAND_LENGTH];
    char upgradeCommand[COMMAND_LENGTH];
    bool enabled;
};

/*********
* Functions
*********/
void printUsage(char* programName) {
    printf("Usage:\n");
    printf("%s search [--exact] <package>\n", programName);
    printf("%s install [--exact] <package>\n", programName);
    printf("%s upgrade\n", programName);
    printf("%s clean\n", programName);
}

bool isInstalled(struct PackageManager* manager) {
    char installedCheck[INSTALL_CHECK_LENGTH];
    snprintf(installedCheck, INSTALL_CHECK_LENGTH, "which %s > /dev/null", manager->name);

    return system(installedCheck) == 0;
}

enum Action parseAction(char* action, bool exactSearch) {
    if (strcmp(action, CLEAN_ACTION) == 0) {
        return Clean;
    } else if (strcmp(action, INSTALL_ACTION) == 0) {
        return Install;
    } else if (strcmp(action, SEARCH_ACTION) == 0) {
        return exactSearch ? SearchExact : Search;
    } else if (strcmp(action, UPGRADE_ACTION) == 0) {
        return Upgrade;
    } else {
        return InvalidAction;
    }
}

void setManager(struct ParsedAction* parsedAction, char* managerName) {
    if (strcmp(managerName, APT) == 0) {
        parsedAction->managers->apt = true;
    } else if (strcmp(managerName, BREW) == 0) {
        parsedAction->managers->flatpak = true;
    } else if (strcmp(managerName, FLATPAK) == 0) {
        parsedAction->managers->flatpak = true;
    } else if (strcmp(managerName, GUIX) == 0) {
        parsedAction->managers->flatpak = true;
    } else if (strcmp(managerName, SNAP) == 0) {
        parsedAction->managers->flatpak = true;
    }
}

void setAllManagers(struct Managers* managers, bool enabled) {
    managers->apt = enabled;
    managers->brew = enabled;
    managers->flatpak = enabled;
    managers->guix = enabled;
    managers->snap = enabled;
}

void setParsedActionDefaults(struct ParsedAction* parsedAction) {
    struct Managers* managers = (struct Managers*)(malloc(sizeof(struct Managers)));
    setAllManagers(managers, true);
    parsedAction->managers = managers;
    parsedAction->action = InvalidAction;
    parsedAction->target = NULL;
    parsedAction->exact = false;
    parsedAction->debug = false;
}

struct ParsedAction* parseOptions(int argc, char *argv[]) {
    int c;
    char *token;

    struct ParsedAction* parsedAction = (struct ParsedAction*)(malloc(sizeof(struct ParsedAction)));
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

char* getCommandForAction(struct PackageManager* manager, struct ParsedAction* parsedAction) {
    switch (parsedAction->action) {
    case Clean:
        return manager->cleanCommand;
        break;
    case Install:
        return manager->installCommand;
        break;
    case Search:
        return manager->searchCommand;
        break;
    case SearchExact:
        return manager->searchExactCommand;
        break;
    case Upgrade:
        return manager->upgradeCommand;
        break;
    default:
        return "";
    }
}

void runCommand(struct PackageManager* manager, struct ParsedAction* parsedAction) {
    printf(DIVIDER);
    printf(DIVIDER);
    printf("%s\n", manager->name);
    printf(DIVIDER);

    char *command = getCommandForAction(manager, parsedAction);

    if (strcmp(command, "") == 0) {
        printf("No relevant command for %s\n", manager->name);

        return;
    }

    printf("%s\n", command);
    if (!parsedAction->debug) {
        system(command);
    }
}

void runCommandForAllManagers(struct PackageManager* managers[], struct ParsedAction* parsedAction) {
    for (int i = 0; i < MANAGERS_COUNT; i++) {
        if (managers[i]->enabled && isInstalled(managers[i])) {
            runCommand(managers[i], parsedAction);
        }
    }
}

void runPackageSearch(struct PackageManager* managers[], struct ParsedAction* parsedAction) {
    struct ParsedAction* searchAction = (struct ParsedAction*)(malloc(sizeof(struct ParsedAction)));
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

void installPackage(struct PackageManager* managers[], struct ParsedAction* parsedAction) {
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

    printf("Installing %s from %s...\n", packageChoice, managers[managerIndex]->name);
    runCommand(managers[managerIndex], parsedAction);
}

void executeAction(struct PackageManager* managers[], struct ParsedAction* parsedAction) {
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

struct PackageManager* definePackageManager(
    const char name[],
    char *cleanCommand,
    char *installCommand,
    char *searchCommand,
    char *searchExactCommand,
    char *upgradeCommand,
    bool enabled
) {
    struct PackageManager* manager = (struct PackageManager*)(malloc(sizeof(struct PackageManager)));
    strncpy(manager->name, name, NAME_LENGTH);
    strncpy(manager->cleanCommand, cleanCommand, COMMAND_LENGTH);
    strncpy(manager->installCommand, installCommand, COMMAND_LENGTH);
    strncpy(manager->searchCommand, searchCommand, COMMAND_LENGTH);
    strncpy(manager->searchExactCommand, searchExactCommand, COMMAND_LENGTH);
    strncpy(manager->upgradeCommand, upgradeCommand, COMMAND_LENGTH);
    manager->enabled = enabled;

    return manager;
}

/*********
* Package Managers
*n********/
struct PackageManager* apt(struct ParsedAction* parsedAction) {
    char cleanCommand[] = "sudo apt autoremove";
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "sudo apt install %s", parsedAction->target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "apt search %s", parsedAction->target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "apt search ^%s$", parsedAction->target);
    char upgradeCommand[] = "sudo apt update; sudo apt upgrade";

    return definePackageManager(APT, cleanCommand, installCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->apt);
}

struct PackageManager* brew(struct ParsedAction* parsedAction) {
    char cleanCommand[] = "brew cleanup";
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "brew install %s", parsedAction->target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "brew search %s", parsedAction->target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "brew search /^%s$/", parsedAction->target);
    char upgradeCommand[] = "brew update; brew upgrade";

    return definePackageManager(BREW, cleanCommand, installCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->brew);
}

struct PackageManager* flatpak(struct ParsedAction* parsedAction) {
    char cleanCommand[] = "flatpak uninstall --unused";
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "flatpak install %s", parsedAction->target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "flatpak search %s", parsedAction->target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "flatpak search %s", parsedAction->target);
    char upgradeCommand[] = "flatpak update";

    return definePackageManager(FLATPAK, cleanCommand, installCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->flatpak);
}

struct PackageManager* guix(struct ParsedAction* parsedAction) {
    char cleanCommand[] = "guix package --delete-generations; guix gc --collect-garbage; guix gc --list-dead";
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "guix install %s", parsedAction->target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "guix package -A %s", parsedAction->target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "guix package -A ^%s$", parsedAction->target);
    char upgradeCommand[] = "guix pull; guix package -u";

    return definePackageManager(GUIX, cleanCommand, installCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->guix);
}

struct PackageManager* snap(struct ParsedAction* parsedAction) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "snap install %s", parsedAction->target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "snap find %s", parsedAction->target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "snap find %s", parsedAction->target);
    char upgradeCommand[] = "sudo snap refresh";

    return definePackageManager(SNAP, "", installCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->snap);
}

/*********
* Main
*********/
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);

        return EXIT_FAILURE;
    }

    struct ParsedAction* parsedAction = parseOptions(argc, argv);

    if (parsedAction->action == InvalidAction) {
        printUsage(argv[0]);

        return EXIT_FAILURE;
    }

    if (parsedAction->action == Help) {
        printUsage(argv[0]);

        return EXIT_SUCCESS;
    }

    struct PackageManager* managers[] = {
        apt(parsedAction),
        brew(parsedAction),
        flatpak(parsedAction),
        guix(parsedAction),
        snap(parsedAction)
    };
    executeAction(managers, parsedAction);

    return EXIT_SUCCESS;
}
