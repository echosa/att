#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZEOF(x)  (sizeof(x) / sizeof((x)[0]))

/*********
* Structs
*********/
struct PackageManagerCommand {
    char args[100];
    bool requiresRoot;
};

struct PackageManager {
    char  name[10];
    struct PackageManagerCommand searchCommand;
};

/*********
* Functions
*********/
struct PackageManagerCommand definePackageManagerCommand(char *name, char *commandArgs, bool requiresRoot) {
    struct PackageManagerCommand command;
    sprintf(command.args, "%s %s", name, commandArgs);
    command.requiresRoot = requiresRoot;

    return command;
}

struct PackageManager definePackageManager(char *name, struct PackageManagerCommand searchCommand) {
    struct PackageManager manager;
    strcpy( manager.name, name);
    manager.searchCommand = searchCommand;

    return manager;
}

void runCommand(struct PackageManager manager, char *command) {
    printf("####################\n");
    printf("####################\n");
    printf("%s\n", manager.name);

    if (strcmp(command, "search") == 0) {
        system(manager.searchCommand.args);
    } else {
        printf("Unrecognized command: %s\n", command);
    }
    printf("####################\n" );
}

/*********
* Package Managers
*********/
struct PackageManager defineAptPackageManager(char *targetPackage) {
    // Name
    char name[] = "apt";

    // Search Command
    char searchCommandArgs[100];
    sprintf(searchCommandArgs, "search %s", targetPackage);
    struct PackageManagerCommand searchCommand = definePackageManagerCommand(name, searchCommandArgs, false);

    return definePackageManager(name, searchCommand);;
}

struct PackageManager defineFlatpakPackageManager(char *targetPackage) {
    // Name
    char name[] = "flatpak";

    // Search Command
    char searchCommandArgs[100];
    sprintf(searchCommandArgs, "search %s", targetPackage);
    struct PackageManagerCommand searchCommand = definePackageManagerCommand(name, searchCommandArgs, false);

    return definePackageManager(name, searchCommand);;
}

/*********
* Main
*********/
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <command> <package>\n", argv[0]);
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
