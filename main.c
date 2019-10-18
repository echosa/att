#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF(x) (sizeof(x) / sizeof((x)[0]))

#define NAME_LENGTH 10
#define COMMAND_LENGTH 100
#define INSTALL_CHECK_LENGTH 50

#define CLEAN_ACTION "clean"
#define SEARCH_ACTION "search"
#define UPGRADE_ACTION "upgrade"

#define DEBUG_OPTION "debug"
#define EXACT_SEARCH_OPTION "exact"
#define HELP_OPTION "help"

enum action { Clean, Search, SearchExact, Upgrade, Help, Invalid };

/*********
* Structs
*********/
struct ParsedAction {
	enum action action;
	char* target;
	bool debug;
};

struct PackageManager {
	char name[NAME_LENGTH];
	char cleanCommand[COMMAND_LENGTH];
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];
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

enum action parseAction(char* action, bool exactSearch) {
	if (strcmp(action, CLEAN_ACTION) == 0) {
		return Clean;
	} else if (strcmp(action, SEARCH_ACTION) == 0) {
		return exactSearch ? SearchExact : Search;
	} else if (strcmp(action, UPGRADE_ACTION) == 0) {
		return Upgrade;
	} else {
		return Invalid;
	}
}

struct ParsedAction* parseOptions(int argc, char *argv[]) {
	int c;
	bool exactSearch = false;
	struct ParsedAction* parsedAction = (struct ParsedAction*)(malloc(sizeof(struct ParsedAction)));
	parsedAction->action = Invalid;
	parsedAction->target = NULL;
	parsedAction->debug = false;

	while (1) {
		int option_index = 0;
		static struct option long_options[] = {
			{ DEBUG_OPTION, no_argument, NULL, 'd' },
			{ EXACT_SEARCH_OPTION, no_argument, NULL, 'e' },
			{ HELP_OPTION, no_argument, NULL, 'h' },
			{ NULL, 0, NULL, 0 }
		};

		c = getopt_long(argc, argv, "eh",  long_options, &option_index);
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

	if ((parsedAction->action == Search || parsedAction->action == SearchExact) && parsedAction->target == NULL) {
		parsedAction->action = Invalid;
	}

	return parsedAction;
}

void runCommand(struct PackageManager* manager, struct ParsedAction* parsedAction) {
	printf("####################\n");
	printf("####################\n");
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

	printf("####################\n");
}

struct PackageManager* definePackageManager(
	char *name,
	char *cleanCommand,
	char *searchCommand,
	char *searchExactCommand,
	char *upgradeCommand
) {
	struct PackageManager* manager = (struct PackageManager*)(malloc(sizeof(struct PackageManager)));
	strncpy(manager->name, name, NAME_LENGTH);
	strncpy(manager->cleanCommand, cleanCommand, COMMAND_LENGTH);
	strncpy(manager->searchCommand, searchCommand, COMMAND_LENGTH);
	strncpy(manager->searchExactCommand, searchExactCommand, COMMAND_LENGTH);
	strncpy(manager->upgradeCommand, upgradeCommand, COMMAND_LENGTH);

	return manager;
}

/*********
* Package Managers
*********/
struct PackageManager* apt(char *targetPackage) {
	char name[] = "apt";
	char cleanCommand[COMMAND_LENGTH];
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	snprintf(cleanCommand, COMMAND_LENGTH, "sudo %s autoremove", name);
	snprintf(searchCommand, COMMAND_LENGTH, "%s search %s", name, targetPackage);
	snprintf(searchExactCommand, COMMAND_LENGTH, "%s search ^%s$", name, targetPackage);
	snprintf(upgradeCommand, COMMAND_LENGTH, "sudo %s upgrade; sudo %s upgrade", name, name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand);
}

struct PackageManager* brew(char *targetPackage) {
	char name[] = "brew";
	char cleanCommand[COMMAND_LENGTH];
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	snprintf(cleanCommand, COMMAND_LENGTH, "%s cleanup", name);
	snprintf(searchCommand, COMMAND_LENGTH, "%s search %s", name, targetPackage);
	snprintf(searchExactCommand, COMMAND_LENGTH, "%s search /^%s$/", name, targetPackage);
	snprintf(upgradeCommand, COMMAND_LENGTH, "%s update; %s upgrade", name, name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand);
}

struct PackageManager* flatpak(char *targetPackage) {
	char name[] = "flatpak";
	char cleanCommand[COMMAND_LENGTH] = "";
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	snprintf(searchCommand, COMMAND_LENGTH, "%s search %s", name, targetPackage);
	snprintf(searchExactCommand, COMMAND_LENGTH, "%s search %s", name, targetPackage);
	snprintf(upgradeCommand, COMMAND_LENGTH, "%s update", name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand);
}

struct PackageManager* guix(char *targetPackage) {
	char name[] = "guix";
	char cleanCommand[COMMAND_LENGTH];
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	snprintf(cleanCommand, COMMAND_LENGTH, "%s package --delete-generations; %s gc --collect-garbage; %s gc --list-dead", name, name, name);
	snprintf(searchCommand, COMMAND_LENGTH, "%s package -A %s", name, targetPackage);
	snprintf(searchExactCommand, COMMAND_LENGTH, "%s package -A ^%s$", name, targetPackage);
	snprintf(upgradeCommand, COMMAND_LENGTH, "%s pull; %s package -u", name, name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand);
}

struct PackageManager* snap(char *targetPackage) {
	char name[] = "snap";
	char cleanCommand[COMMAND_LENGTH] = "";
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	snprintf(searchCommand, COMMAND_LENGTH, "%s find %s", name, targetPackage);
	snprintf(searchExactCommand, COMMAND_LENGTH, "%s find %s", name, targetPackage);
	snprintf(upgradeCommand, COMMAND_LENGTH, "sudo %s refresh", name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand);
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
		apt(parsedAction->target),
		brew(parsedAction->target),
		flatpak(parsedAction->target),
		guix(parsedAction->target),
		snap(parsedAction->target)
	};

	char installedCheck[INSTALL_CHECK_LENGTH];
	for (int i = 0; i < SIZE_OF(managers); i++) {
		snprintf(installedCheck, INSTALL_CHECK_LENGTH, "which %s > /dev/null", managers[i]->name);
		if (system(installedCheck) == 0) {
			runCommand(managers[i], parsedAction);
		}
	}

	return EXIT_SUCCESS;
}
