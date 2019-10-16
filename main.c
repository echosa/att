#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZEOF(x)  (sizeof(x) / sizeof((x)[0]))
#define PRINT_INSTEAD_OF_RUN true

/*********
* Structs
*********/
struct PackageManager {
    char  name[10];
    char cleanCommand[100];
    char searchCommand[100];
    char updateCommand[100];
};

/*********
* Functions
*********/
struct PackageManager definePackageManager(
    char *name,
    char *cleanCommand,
    char *searchCommand,
    char *updateCommand
) {
    struct PackageManager manager;
    strcpy( manager.name, name);
    strcpy(manager.cleanCommand, cleanCommand);
    strcpy(manager.searchCommand, searchCommand);
    strcpy(manager.updateCommand, updateCommand);

    return manager;
}

void runCommand(struct PackageManager manager, char *action) {
    printf("####################\n");
    printf("####################\n");
    printf("%s\n", manager.name);

    if (strcmp(action, "clean") == 0) {
        if (PRINT_INSTEAD_OF_RUN) {
            printf("%s\n", manager.cleanCommand);
        } else {
            system(manager.cleanCommand);
        }
    } else if (strcmp(action, "search") == 0) {
        if (PRINT_INSTEAD_OF_RUN) {
            printf("%s\n", manager.searchCommand);
        } else {
            system(manager.searchCommand);
        }
    } else if (strcmp(action, "update") == 0) {
        if (PRINT_INSTEAD_OF_RUN) {
            printf("%s\n", manager.updateCommand);
        } else {
            system(manager.updateCommand);
        }
    } else {
        printf("Unrecognized action: %s\n", action);
    }
    printf("####################\n" );
}

/*********
* Package Managers
*********/
struct PackageManager defineAptPackageManager(char *targetPackage) {
    char name[] = "apt";
    char cleanCommand[100];
    char searchCommand[100];
    char updateCommand[100];

    sprintf(cleanCommand, "sudo %s autoremove", name);
    sprintf(searchCommand, "%s search %s", name, targetPackage);
    sprintf(updateCommand, "sudo %s update; sudo %s upgrade", name, name);

    return definePackageManager(name, cleanCommand, searchCommand, updateCommand);
}

struct PackageManager defineFlatpakPackageManager(char *targetPackage) {
    char name[] = "flatpak";
    char cleanCommand[100];
    char searchCommand[100];
    char updateCommand[100];

    sprintf(cleanCommand, "No 'clean' command for %s", name);
    sprintf(searchCommand, "%s search %s", name, targetPackage);
    sprintf(updateCommand, "%s update", name);

    return definePackageManager(name, cleanCommand, searchCommand, updateCommand);
}

/*********
* Main
*********/
int main(int argc, char *argv[]) {
    if (argc < 1) {
        printf("Usage: %s <action> [package]\n", argv[0]);
        return 1;
    }

    char *action = argv[1];
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
