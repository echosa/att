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
struct PackageManager defineApt() {
    struct PackageManager apt;
    strcpy( apt.name, "apt");

    struct PackageManagerCommand searchCommand;
    strcpy(searchCommand.args, "search emacs");
    apt.searchCommand = searchCommand;

    return apt;
}

int main() {
    struct PackageManager managers[] = {
         defineApt()
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
