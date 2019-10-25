#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 10
#define COMMAND_LENGTH 100
#define INSTALL_CHECK_LENGTH 50

static const char CLEAN_ACTION[] = "clean";
static const char INSTALL_ACTION[] = "install";
static const char SEARCH_ACTION[] = "search";
static const char UPGRADE_ACTION[] = "upgrade";

static const char DEBUG_OPTION[] = "debug";
static const char EXACT_SEARCH_OPTION[] = "exact";
static const char HELP_OPTION[] = "help";
static const char MANAGERS_OPTION[] = "managers";

static const char DIVIDER[] = "####################\n";

enum Action { Clean, Install, Search, SearchExact, Upgrade, Help, Invalid };

enum PackageManagers { Apt, Brew, Flatpak, Guix, Snap };
static const int MANAGERS_COUNT = 5;

static struct option long_options[] = {
    { DEBUG_OPTION, no_argument, NULL, 'd' },
    { EXACT_SEARCH_OPTION, no_argument, NULL, 'e' },
    { HELP_OPTION, no_argument, NULL, 'h' },
    { MANAGERS_OPTION, required_argument, NULL, 'm' },
    { NULL, 0, NULL, 0 }
};

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
        return Invalid;
    }
}

void setManager(struct ParsedAction* parsedAction, char* managerName) {
    if (strcmp(managerName, "apt") == 0) {
        parsedAction->managers->apt = true;
    } else if (strcmp(managerName, "brew") == 0) {
        parsedAction->managers->flatpak = true;
    } else if (strcmp(managerName, "flatpak") == 0) {
        parsedAction->managers->flatpak = true;
    } else if (strcmp(managerName, "guix") == 0) {
        parsedAction->managers->flatpak = true;
    } else if (strcmp(managerName, "snap") == 0) {
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

struct ParsedAction* parseOptions(int argc, char *argv[]) {
    int c;
    char *token;

    struct ParsedAction* parsedAction = (struct ParsedAction*)(malloc(sizeof(struct ParsedAction)));
    struct Managers* managers = (struct Managers*)(malloc(sizeof(struct Managers)));
    setAllManagers(managers, true);
    parsedAction->managers = managers;
    parsedAction->action = Invalid;
    parsedAction->target = NULL;
    parsedAction->exact = false;
    parsedAction->debug = false;

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
        parsedAction->action = Invalid;

        return parsedAction;
    }

    if (optind < argc) {
        parsedAction->action = parseAction(argv[optind++], parsedAction->exact);
    }
    if (optind < argc) {
        parsedAction->target = argv[optind++];
    }

    if ((parsedAction->action == Search || parsedAction->action == SearchExact || parsedAction->action == Install) && parsedAction->target == NULL) {
        parsedAction->action = Invalid;
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

int getManagerIndex(char* managerName) {
    if (strcmp(managerName, "apt") == 0) {
        return Apt;
    } else if (strcmp(managerName, "brew") == 0) {
        return Brew;
    } else if (strcmp(managerName, "flatpak") == 0) {
        return Flatpak;
    } else if (strcmp(managerName, "guix") == 0) {
        return Guix;
    } else if (strcmp(managerName, "snap") == 0) {
        return Snap;
    } else {
        return -1;
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
    char *name,
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
*********/
struct PackageManager* apt(struct ParsedAction* parsedAction) {
    char name[] = "apt";
    char cleanCommand[COMMAND_LENGTH];
    char installCommand[COMMAND_LENGTH];
    char searchCommand[COMMAND_LENGTH];
    char searchExactCommand[COMMAND_LENGTH];
    char upgradeCommand[COMMAND_LENGTH];

    snprintf(cleanCommand, COMMAND_LENGTH, "sudo %s autoremove", name);
    snprintf(installCommand, COMMAND_LENGTH, "sudo %s install %s", name, parsedAction->target);
    snprintf(searchCommand, COMMAND_LENGTH, "%s search %s", name, parsedAction->target);
    snprintf(searchExactCommand, COMMAND_LENGTH, "%s search ^%s$", name, parsedAction->target);
    snprintf(upgradeCommand, COMMAND_LENGTH, "sudo %s update; sudo %s upgrade", name, name);

    return definePackageManager(name, cleanCommand, installCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->apt);
}

struct PackageManager* brew(struct ParsedAction* parsedAction) {
    char name[] = "brew";
    char cleanCommand[COMMAND_LENGTH];
    char installCommand[COMMAND_LENGTH];
    char searchCommand[COMMAND_LENGTH];
    char searchExactCommand[COMMAND_LENGTH];
    char upgradeCommand[COMMAND_LENGTH];

    snprintf(cleanCommand, COMMAND_LENGTH, "%s cleanup", name);
    snprintf(installCommand, COMMAND_LENGTH, "%s install %s", name, parsedAction->target);
    snprintf(searchCommand, COMMAND_LENGTH, "%s search %s", name, parsedAction->target);
    snprintf(searchExactCommand, COMMAND_LENGTH, "%s search /^%s$/", name, parsedAction->target);
    snprintf(upgradeCommand, COMMAND_LENGTH, "%s update; %s upgrade", name, name);

    return definePackageManager(name, cleanCommand, installCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->brew);
}

struct PackageManager* flatpak(struct ParsedAction* parsedAction) {
    char name[] = "flatpak";
    char cleanCommand[COMMAND_LENGTH];
    char installCommand[COMMAND_LENGTH];
    char searchCommand[COMMAND_LENGTH];
    char searchExactCommand[COMMAND_LENGTH];
    char upgradeCommand[COMMAND_LENGTH];

    snprintf(cleanCommand, COMMAND_LENGTH, "%s uninstall --unused", name);
    snprintf(installCommand, COMMAND_LENGTH, "%s install %s", name, parsedAction->target);
    snprintf(searchCommand, COMMAND_LENGTH, "%s search %s", name, parsedAction->target);
    snprintf(searchExactCommand, COMMAND_LENGTH, "%s search %s", name, parsedAction->target);
    snprintf(upgradeCommand, COMMAND_LENGTH, "%s update", name);

    return definePackageManager(name, cleanCommand, installCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->flatpak);
}

struct PackageManager* guix(struct ParsedAction* parsedAction) {
    char name[] = "guix";
    char cleanCommand[COMMAND_LENGTH];
    char installCommand[COMMAND_LENGTH];
    char searchCommand[COMMAND_LENGTH];
    char searchExactCommand[COMMAND_LENGTH];
    char upgradeCommand[COMMAND_LENGTH];

    snprintf(cleanCommand, COMMAND_LENGTH, "%s package --delete-generations; %s gc --collect-garbage; %s gc --list-dead", name, name, name);
    snprintf(installCommand, COMMAND_LENGTH, "%s install %s", name, parsedAction->target);
    snprintf(searchCommand, COMMAND_LENGTH, "%s package -A %s", name, parsedAction->target);
    snprintf(searchExactCommand, COMMAND_LENGTH, "%s package -A ^%s$", name, parsedAction->target);
    snprintf(upgradeCommand, COMMAND_LENGTH, "%s pull; %s package -u", name, name);

    return definePackageManager(name, cleanCommand, installCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->guix);
}

struct PackageManager* snap(struct ParsedAction* parsedAction) {
    char name[] = "snap";
    char installCommand[COMMAND_LENGTH];
    char searchCommand[COMMAND_LENGTH];
    char searchExactCommand[COMMAND_LENGTH];
    char upgradeCommand[COMMAND_LENGTH];

    snprintf(installCommand, COMMAND_LENGTH, "%s install %s", name, parsedAction->target);
    snprintf(searchCommand, COMMAND_LENGTH, "%s find %s", name, parsedAction->target);
    snprintf(searchExactCommand, COMMAND_LENGTH, "%s find %s", name, parsedAction->target);
    snprintf(upgradeCommand, COMMAND_LENGTH, "sudo %s refresh", name);

    return definePackageManager(name, "", installCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->snap);
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

    if (parsedAction->action == Invalid) {
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
