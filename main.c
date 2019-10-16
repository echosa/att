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
    char searchCommand[200];
    char updateCommand[200];
};

/*********
* Functions
*********/
struct PackageManager definePackageManager(char *name, char *searchCommand, char *updateCommand) {
    struct PackageManager manager;
    strcpy( manager.name, name);
    strcpy(manager.searchCommand, searchCommand);
    strcpy(manager.updateCommand, updateCommand);

    return manager;
}

void runCommand(struct PackageManager manager, char *command) {
    printf("####################\n");
    printf("####################\n");
    printf("%s\n", manager.name);

    if (strcmp(command, "search") == 0) {
        if (PRINT_INSTEAD_OF_RUN) {
            printf("%s\n", manager.searchCommand);
        } else {
            system(manager.searchCommand);
        }
    } else if (strcmp(command, "update") == 0) {
        if (PRINT_INSTEAD_OF_RUN) {
            printf("%s\n", manager.updateCommand);
        } else {
            system(manager.updateCommand);
        }
    } else {
        printf("Unrecognized command: %s\n", command);
    }
    printf("####################\n" );
}

/*********
* Package Managers
*********/
struct PackageManager defineAptPackageManager(char *targetPackage) {
    char name[] = "apt";
    char searchCommand[100];
    char updateCommand[100];

    sprintf(searchCommand, "%s search %s", name, targetPackage);
    sprintf(updateCommand, "sudo %s update; sudo %s upgrade", name, name);

    return definePackageManager(name, searchCommand, updateCommand);
}

struct PackageManager defineFlatpakPackageManager(char *targetPackage) {
    char name[] = "flatpak";
    char searchCommand[100];
    char updateCommand[100];

    sprintf(searchCommand, "%s search %s", name, targetPackage);
    sprintf(updateCommand, "%s update", name);

    return definePackageManager(name, searchCommand, updateCommand);
}

/*********
* Main
*********/
int main(int argc, char *argv[]) {
    if (argc < 1) {
        printf("Usage: %s <command> [package]\n", argv[0]);
        return 1;
    }

    char *command = argv[1];
    char *targetPackage = argv[2];

    struct PackageManager managers[] = {
         defineAptPackageManager(targetPackage),
         defineFlatpakPackageManager(targetPackage)
    };

    for (int i = 0; i < SIZEOF(managers); i++) {
        runCommand(managers[i], command);
    }

    return 0;
}
