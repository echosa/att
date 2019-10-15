#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZEOF(x)  (sizeof(x) / sizeof((x)[0]))

/*********
* Structs
*********/
struct PackageManagerCommand {
    char args[20];
    bool requiresRoot;
};

struct PackageManager {
    char  name[10];
    struct PackageManagerCommand searchCommand;
};

/*********
* Functions
*********/
struct PackageManagerCommand definePackageManagerCommand(char name[10], char commandArgs[50], bool requiresRoot) {
    struct PackageManagerCommand command;
    sprintf(command.args, "%s %s", name, commandArgs);
    command.requiresRoot = requiresRoot;

    return command;
}

struct PackageManager definePackageManager(char name[10], struct PackageManagerCommand searchCommand) {
    struct PackageManager manager;
    strcpy( manager.name, name);
    manager.searchCommand = searchCommand;

    return manager;
}

void runCommand(struct PackageManager manager, char *command) {
    if (strcmp(command, "search") == 0) {
        system(manager.searchCommand.args);
    } else {
        printf("Unrecognized command: %s\n", command);
    }
}


/*********
* Package Managers
*********/
struct PackageManager defineAptPackageManager(char targetPackage[]) {
    // Name
    char name[10] = "apt";

    // Search Command
    char searchCommandArgs[50];
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
         defineAptPackageManager(targetPackage)
    };

    for (int i = 0; i < SIZEOF(managers); i++) {
        printf("####################\n");
        printf("####################\n");
        printf("%s\n", managers[i].name);
        runCommand(managers[i], command);
        printf("####################\n" );
    }

    return 0;
}
