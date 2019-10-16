#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DO_NOT_RUN false
#define COMMAND_LENGTH 100
#define SIZEOF(x)  (sizeof(x) / sizeof((x)[0]))
#define CLEAN_ACTION "clean"
#define SEARCH_ACTION "search"
#define SEARCH_EXACT_ACTION "exact"
#define UPGRADE_ACTION "upgrade"

enum action { Clean, Search, SearchExact, Upgrade, Invalid };

/*********
* Structs
*********/
struct PackageManager {
	char  name[10];
	char cleanCommand[COMMAND_LENGTH];
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];
};

/*********
* Functions
*********/
enum action parseAction(char* action) {
	if (strcmp(action, CLEAN_ACTION) == 0) {
		return Clean;
	} else if (strcmp(action, SEARCH_ACTION) == 0) {
		return Search;
	 } else if (strcmp(action, SEARCH_EXACT_ACTION) == 0) {
		return SearchExact;
	} else if (strcmp(action, UPGRADE_ACTION) == 0) {
		return Upgrade;
	} else {
		return Invalid;
	}
}

void runCommand(struct PackageManager manager, enum action action) {
	printf("####################\n");
	printf("####################\n");
	printf("%s\n", manager.name);

	char *command;
	if (action == Clean) {
		command = manager.cleanCommand;
	} else if (action == Search) {
		command = manager.searchCommand;
	} else if (action == SearchExact) {
		command = manager.searchExactCommand;
	} else if (action == Upgrade) {
		command = manager.upgradeCommand;
	}

	if (strcmp(command, "") == 0) {
		printf("No relevant command for %s\n", manager.name);
	} else {
		printf("%s\n", command);
		if (!DO_NOT_RUN) {
			system(command);
		}
	}

   printf("####################\n" );
}

struct PackageManager definePackageManager(
	char *name,
	char *cleanCommand,
	char *searchCommand,
	char *searchExactCommand,
	char *upgradeCommand
) {
	struct PackageManager manager;
	strcpy(manager.name, name);
	strcpy(manager.cleanCommand, cleanCommand);
	strcpy(manager.searchCommand, searchCommand);
	strcpy(manager.searchExactCommand, searchExactCommand);
	strcpy(manager.upgradeCommand, upgradeCommand);

	return manager;
}

/*********
* Package Managers
*********/
struct PackageManager apt(char *targetPackage) {
	char name[] = "apt";
	char cleanCommand[COMMAND_LENGTH];
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	sprintf(cleanCommand, "sudo %s autoremove", name);
	sprintf(searchCommand, "%s search %s", name, targetPackage);
	sprintf(searchExactCommand, "%s search ^%s$", name, targetPackage);
	sprintf(upgradeCommand, "sudo %s upgrade; sudo %s upgrade", name, name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand);
}

struct PackageManager brew(char *targetPackage) {
	char name[] = "brew";
	char cleanCommand[COMMAND_LENGTH];
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	sprintf(cleanCommand, "%s cleanup", name);
	sprintf(searchCommand, "%s search %s", name, targetPackage);
	sprintf(searchExactCommand, "%s search /^%s$/", name, targetPackage);
	sprintf(upgradeCommand, "%s update; %s upgrade", name, name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand);
}

struct PackageManager flatpak(char *targetPackage) {
	char name[] = "flatpak";
	char cleanCommand[COMMAND_LENGTH] = "";
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	sprintf(searchCommand, "%s search %s", name, targetPackage);
	sprintf(searchExactCommand, "%s search %s", name, targetPackage);
	sprintf(upgradeCommand, "%s upgrade", name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand);
}

struct PackageManager guix(char *targetPackage) {
	char name[] = "guix";
	char cleanCommand[COMMAND_LENGTH];
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	sprintf(cleanCommand, "%s package --delete-generations; %s gc --collect-garbage; %s gc --list-dead", name, name, name);
	sprintf(searchCommand, "%s package -A %s", name, targetPackage);
	sprintf(searchExactCommand, "%s package -A ^%s$", name, targetPackage);
	sprintf(upgradeCommand, "%s pull; %s package -U", name, name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand);
}

struct PackageManager snap(char *targetPackage) {
	char name[] = "snap";
	char cleanCommand[COMMAND_LENGTH] = "";
	char searchCommand[COMMAND_LENGTH];
	char searchExactCommand[COMMAND_LENGTH];
	char upgradeCommand[COMMAND_LENGTH];

	sprintf(searchCommand, "%s find %s", name, targetPackage);
	sprintf(searchExactCommand, "%s find %s", name, targetPackage);
	sprintf(upgradeCommand, "sudo %s refresh", name);

	return definePackageManager(name, cleanCommand, searchCommand, searchExactCommand, upgradeCommand);
}

/*********
* Main
*********/
int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <action> [package]\n", argv[0]);
		return 1;
	}

	enum action action = parseAction(argv[1]);
	if (action == Invalid) {
		printf("Invalid action: %s\n", argv[1]);

		return 1;
	} else if ((action == Search || action == SearchExact) && argc < 3) {
		printf("Usage: %s <action> package\n", argv[0]);
		return 1;
	}

	char *targetPackage = argv[2];

	struct PackageManager managers[] = {
		apt(targetPackage),
		brew(targetPackage),
		flatpak(targetPackage),
		guix(targetPackage),
		snap(targetPackage)
	};

	for (int i = 0; i < SIZEOF(managers); i++) {
		runCommand(managers[i], action);
	}

	return 0;
}
