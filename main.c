#include <stdbool.h>
#include <stdio.h>
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
struct PackageManager definePackageManager(char name[10], char targetPackage[]) {
    struct PackageManager manager;
    strcpy( manager.name, name);

    struct PackageManagerCommand searchCommand;
    char command[50];
    sprintf(command, "%s %s %s", manager.name, "search", targetPackage);
    strcpy(searchCommand.args, command);
    manager.searchCommand = searchCommand;

    return manager;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please specify a package name.\n");
        return 1;
    }

    char *targetPackage = argv[1];
    struct PackageManager managers[] = {
         definePackageManager("apt", targetPackage)
    };

    for (int i = 0; i < SIZEOF(managers); i++) {
        printf("####################\n");
        printf("####################\n");
        printf("%s\n", managers[i].name);
        printf("%s\n", managers[i].searchCommand.args);
        printf("####################\n" );
    }

    return 0;
}
