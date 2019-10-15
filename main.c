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
struct PackageManager defineApt(char targetPackage[]) {
    struct PackageManager apt;
    strcpy( apt.name, "apt");

    struct PackageManagerCommand searchCommand;
    char command[50] = "search ";
    strcat(command, targetPackage);
    strcpy(searchCommand.args, command);
    apt.searchCommand = searchCommand;

    return apt;
}

int main() {
    char targetPackage[] = "emacs";
    struct PackageManager managers[] = {
         defineApt(targetPackage)
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
