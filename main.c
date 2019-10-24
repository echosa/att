#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF(x) (sizeof(x) / sizeof((x)[0]))

#define NAME_LENGTH 10
#define COMMAND_LENGTH 100

static const int INSTALL_CHECK_LENGTH = 50;

static const char CLEAN_ACTION[] = "clean";
static const char INSTALL_ACTION[] = "install";
static const char SEARCH_ACTION[] = "search";
static const char UPGRADE_ACTION[] = "upgrade";

static const char DEBUG_OPTION[] = "debug";
static const char EXACT_SEARCH_OPTION[] = "exact";
static const char HELP_OPTION[] = "help";
static const char MANAGERS_OPTION[] = "managers";

static const char DIVIDER[] = "####################\n";

enum action { Clean, Install, Search, SearchExact, Upgrade, Help, Invalid };

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
	enum action action;
	char* target;
	bool debug;
	struct Managers* managers;
};

struct PackageManager {
	char name[NAME_LENGTH];
	char cleanCommand[COMMAND_LENGTH];
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
	printf("%s upgrade\n", programName);
	printf("%s clean\n", programName);
}

bool isInstalled(struct PackageManager* manager) {
	char installedCheck[INSTALL_CHECK_LENGTH];
	snprintf(installedCheck, INSTALL_CHECK_LENGTH, "which %s > /dev/null", manager->name);

	return system(installedCheck) == 0;
}

enum action parseAction(char* action, bool exactSearch) {
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

struct Managers* setAllManagers() {
	struct Managers* managers = (struct Managers*)(malloc(sizeof(struct Managers)));
	managers->apt = true;
	managers->brew = true;
	managers->flatpak = true;
	managers->guix = true;
	managers->snap = true;
	return managers;
}

struct ParsedAction* parseOptions(int argc, char *argv[]) {
	int c;
	bool exactSearch = false;
	char *token;

	struct ParsedAction* parsedAction = (struct ParsedAction*)(malloc(sizeof(struct ParsedAction)));
	parsedAction->action = Invalid;
	parsedAction->target = NULL;
	parsedAction->debug = false;
	parsedAction->managers = setAllManagers();

	while (1) {
		int option_index = 0;
		static struct option long_options[] = {
			{ DEBUG_OPTION, no_argument, NULL, 'd' },
			{ EXACT_SEARCH_OPTION, no_argument, NULL, 'e' },
			{ HELP_OPTION, no_argument, NULL, 'h' },
			{ MANAGERS_OPTION, required_argument, NULL, 'm' },
			{ NULL, 0, NULL, 0 }
		};

		c = getopt_long(argc, argv, "dehm",  long_options, &option_index);
		if (c == -1) {
			break;
		}

		switch (c) {
		case 'd':
			parsedAction->debug = true;
			break;

		case 'e':
			exactSearch = true;
			break;

		case 'h':
			parsedAction->action = Help;
			return parsedAction;

		case 'm':
			parsedAction->managers->apt = false;
			parsedAction->managers->brew = false;
			parsedAction->managers->flatpak = false;
			parsedAction->managers->guix = false;
			parsedAction->managers->snap = false;

			while ((token = strsep(&optarg, ",")) != NULL) {
				if (strcmp(token, "apt") == 0) {
					parsedAction->managers->apt = true;
				} else if (strcmp(token, "brew") == 0) {
					parsedAction->managers->flatpak = true;
				} else if (strcmp(token, "flatpak") == 0) {
					parsedAction->managers->flatpak = true;
				} else if (strcmp(token, "guix") == 0) {
					parsedAction->managers->flatpak = true;
				} else if (strcmp(token, "snap") == 0) {
					parsedAction->managers->flatpak = true;
				}
			}

		}
	}

	if (optind >= argc) {
		parsedAction->action = Invalid;
		return parsedAction;
	}

	if (optind < argc) {
		parsedAction->action = parseAction(argv[optind++], exactSearch);
	}
	if (optind < argc) {
		parsedAction->target = argv[optind++];
	}

	if ((parsedAction->action == Search || parsedAction->action == SearchExact || parsedAction->action == Install) && parsedAction->target == NULL) {
		parsedAction->action = Invalid;
	}

	return parsedAction;
}

void installPackage(struct PackageManager* managers[], struct ParsedAction* parsedAction) {
	printf("Package installation not yet supported.\n");
	//printf("Searching for package to install...\n");
	// loop through all managers and do an exact search for the target
	// parse and present results to user
	// allow user to select result
	// install the selected result
}

void runCommand(struct PackageManager* manager, struct ParsedAction* parsedAction) {
	printf(DIVIDER);
	printf(DIVIDER);
	printf("%s\n", manager->name);

	char *command;
	if (parsedAction->action == Clean) {
		command = manager->cleanCommand;
	} else if (parsedAction->action == Search) {
		command = manager->searchCommand;
	} else if (parsedAction->action == SearchExact) {
		command = manager->searchExactCommand;
	} else if (parsedAction->action == Upgrade) {
		command = manager->upgradeCommand;
	}

	if (strcmp(command, "") == 0) {
		printf("No relevant command for %s\n", manager->name);
	} else {
		printf("%s\n", command);
		if (!parsedAction->debug) {
			system(command);
		}
	}
}

struct PackageManager* definePackageManager(
	char *name,
	char *cleanCommand,
	char *searchCommand,
	char *searchExactCommand,
	char *upgradeCommand,
	bool enabled
) {
	struct PackageManager* manager = (struct PackageManager*)(malloc(sizeof(struct PackageManager)));
	strncpy(manager->name, name, NAME_LENGTH);
	strncpy(manager->cleanCommand, cleanCommand, COMMAND_LENGTH);
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
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	snprintf(cleanCommand, COMMAND_LENGTH, "sudo %s autoremove", name);
	snprintf(searchCommand, COMMAND_LENGTH, "%s search %s", name, parsedAction->target);
	snprintf(searchExactCommand, COMMAND_LENGTH, "%s search ^%s$", name, parsedAction->target);
	snprintf(upgradeCommand, COMMAND_LENGTH, "sudo %s update; sudo %s upgrade", name, name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->apt);
}

struct PackageManager* brew(struct ParsedAction* parsedAction) {
	char name[] = "brew";
	char cleanCommand[COMMAND_LENGTH];
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	snprintf(cleanCommand, COMMAND_LENGTH, "%s cleanup", name);
	snprintf(searchCommand, COMMAND_LENGTH, "%s search %s", name, parsedAction->target);
	snprintf(searchExactCommand, COMMAND_LENGTH, "%s search /^%s$/", name, parsedAction->target);
	snprintf(upgradeCommand, COMMAND_LENGTH, "%s update; %s upgrade", name, name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->brew);
}

struct PackageManager* flatpak(struct ParsedAction* parsedAction) {
	char name[] = "flatpak";
	char cleanCommand[COMMAND_LENGTH];
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	snprintf(cleanCommand, COMMAND_LENGTH, "%s uninstall --unused", name);
	snprintf(searchCommand, COMMAND_LENGTH, "%s search %s", name, parsedAction->target);
	snprintf(searchExactCommand, COMMAND_LENGTH, "%s search %s", name, parsedAction->target);
	snprintf(upgradeCommand, COMMAND_LENGTH, "%s update", name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->flatpak);
}

struct PackageManager* guix(struct ParsedAction* parsedAction) {
	char name[] = "guix";
	char cleanCommand[COMMAND_LENGTH];
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	snprintf(cleanCommand, COMMAND_LENGTH, "%s package --delete-generations; %s gc --collect-garbage; %s gc --list-dead", name, name, name);
	snprintf(searchCommand, COMMAND_LENGTH, "%s package -A %s", name, parsedAction->target);
	snprintf(searchExactCommand, COMMAND_LENGTH, "%s package -A ^%s$", name, parsedAction->target);
	snprintf(upgradeCommand, COMMAND_LENGTH, "%s pull; %s package -u", name, name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->guix);
}

struct PackageManager* snap(struct ParsedAction* parsedAction) {
	char name[] = "snap";
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	snprintf(searchCommand, COMMAND_LENGTH, "%s find %s", name, parsedAction->target);
	snprintf(searchExactCommand, COMMAND_LENGTH, "%s find %s", name, parsedAction->target);
	snprintf(upgradeCommand, COMMAND_LENGTH, "sudo %s refresh", name);

	return definePackageManager(name, "", searchCommand, searchExactCommand, upgradeCommand, parsedAction->managers->snap);
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

	struct PackageManager *managers[] = {
		apt(parsedAction),
		brew(parsedAction),
		flatpak(parsedAction),
		guix(parsedAction),
		snap(parsedAction)
	};

	if (parsedAction->action == Install) {
		installPackage(managers, parsedAction);
	} else {
		for (long unsigned int i = 0; i < SIZE_OF(managers); i++) {
			if (managers[i]->enabled && isInstalled(managers[i])) {
				runCommand(managers[i], parsedAction);
			}
		}
	}

	return EXIT_SUCCESS;
}
