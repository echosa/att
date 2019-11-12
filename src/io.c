#include <stdio.h>
#include "io.h"
#include "supported_manager.h"
#include "commands.h"

void printUsage(char* programName) {
    printf("Usage:\n");
    printf("%s search [--exact] <package>\n", programName);
    printf("%s install [--exact] <package>\n", programName);
    printf("%s upgrade\n", programName);
    printf("%s clean\n", programName);
    printf("%s which\n", programName);
}

int promptForManager() {
    char managerChoice[COMMAND_LENGTH];
    scanf("%s", managerChoice);

    return getManagerIndex(managerChoice);
}
