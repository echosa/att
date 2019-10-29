#include <stdlib.h>
#include <string.h>
#include "commands.h"

struct Commands {
    char clean[COMMAND_LENGTH];
    char install[COMMAND_LENGTH];
    char search[COMMAND_LENGTH];
    char searchExact[COMMAND_LENGTH];
    char upgrade[COMMAND_LENGTH];
};

Commands* commands_new() {
    Commands* commands = (Commands*) malloc(sizeof(Commands));

    return commands;
}

void setCleanCommand(Commands *commands, char* command) {
    strncpy(commands->clean, command, COMMAND_LENGTH);
}

void setInstallCommand(Commands *commands, char* command) {
    strncpy(commands->install, command, COMMAND_LENGTH);
}

void setSearchCommand(Commands *commands, char* command) {
    strncpy(commands->search, command, COMMAND_LENGTH);
}

void setSearchExactCommand(Commands *commands, char* command) {
    strncpy(commands->searchExact, command, COMMAND_LENGTH);
}

void setUpgradeCommand(Commands *commands, char* command) {
    strncpy(commands->upgrade, command, COMMAND_LENGTH);
}

char* getCleanCommand(Commands *commands) {
    return commands->clean;
}

char* getInstallCommand(Commands *commands) {
    return commands->install;
}

char* getSearchCommand(Commands *commands) {
    return commands->search;
}

char* getSearchExactCommand(Commands *commands) {
    return commands->searchExact;
}

char* getUpgradeCommand(Commands *commands) {
    return commands->upgrade;
}
