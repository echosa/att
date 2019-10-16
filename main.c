#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_INSTEAD_OF_RUN true
#define SIZEOF(x)  (sizeof(x) / sizeof((x)[0]))

enum action { Clean, Search, Upgrade, Invalid };

/*********
* Structs
*********/
struct PackageManager {
    char  name[10];
    char cleanCommand[100];
    char searchCommand[100];
    char upgradeCommand[100];
};

/*********
* Functions
*********/
enum action parseAction(char* action) {
    if (strcmp(action, "clean") == 0) {
        return Clean;
    } else if (strcmp(action, "search") == 0) {
        return Search;
    } else if (strcmp(action, "upgrade") == 0) {
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
    } else if (action == Upgrade) {
        command = manager.upgradeCommand;
    }

    if (PRINT_INSTEAD_OF_RUN) {
        printf("%s\n", command);
    } else {
        system(command);
    }

   printf("####################\n" );
}

/*********
* Package Managers
*********/
struct PackageManager definePackageManager(
    char *name,
    char *cleanCommand,
    char *searchCommand,
    char *upgradeCommand
) {
    struct PackageManager manager;
    strcpy( manager.name, name);
    strcpy(manager.cleanCommand, cleanCommand);
    strcpy(manager.searchCommand, searchCommand);
    strcpy(manager.upgradeCommand, upgradeCommand);

    return manager;
}

struct PackageManager defineAptPackageManager(char *targetPackage) {
    char name[] = "apt";
    char cleanCommand[100];
    char searchCommand[100];
    char upgradeCommand[100];

    sprintf(cleanCommand, "sudo %s autoremove", name);
    sprintf(searchCommand, "%s search %s", name, targetPackage);
    sprintf(upgradeCommand, "sudo %s upgrade; sudo %s upgrade", name, name);

    return definePackageManager(name, cleanCommand, searchCommand, upgradeCommand);
}

struct PackageManager defineFlatpakPackageManager(char *targetPackage) {
    char name[] = "flatpak";
    char cleanCommand[100];
    char searchCommand[100];
    char upgradeCommand[100];

    sprintf(cleanCommand, "No 'clean' command for %s", name);
    sprintf(searchCommand, "%s search %s", name, targetPackage);
    sprintf(upgradeCommand, "%s upgrade", name);

    return definePackageManager(name, cleanCommand, searchCommand, upgradeCommand);
}

/*********
* Main
*********/
int main(int argc, char *argv[]) {
    if (argc < 1) {
        printf("Usage: %s <action> [package]\n", argv[0]);
        return 1;
    }

    enum action action = parseAction(argv[1]);
    if (action == Invalid) {
        printf("Invalid action: %s\n", argv[1]);

        return 1;
    }

    char *targetPackage = argv[2];

    struct PackageManager managers[] = {
         defineAptPackageManager(targetPackage),
         defineFlatpakPackageManager(targetPackage)
    };

    for (int i = 0; i < SIZEOF(managers); i++) {
        runCommand(managers[i], action);
    }

    return 0;
}
