#include <stdlib.h>
#include <string.h>
#include "commands.h"

struct Commands {
    char clean[COMMAND_LENGTH];
    char install[COMMAND_LENGTH];
    char search[COMMAND_LENGTH];
    char searchExact[COMMAND_LENGTH];
    char upgrade[COMMAND_LENGTH];
    char which[COMMAND_LENGTH];
};

Commands* commands_new() {
    Commands* commands = (Commands*) malloc(sizeof(Commands));

    return commands;
}

void setCommand(Commands *commands, enum Action action, char* command) {
    if (action == Clean) {
        strncpy(commands->clean, command, COMMAND_LENGTH);
    } else if (action == Install) {
        strncpy(commands->install, command, COMMAND_LENGTH);
    } else if (action == Search) {
        strncpy(commands->search, command, COMMAND_LENGTH);
    } else if (action == SearchExact) {
        strncpy(commands->searchExact, command, COMMAND_LENGTH);
    } else if (action == Upgrade) {
        strncpy(commands->upgrade, command, COMMAND_LENGTH);
    } else if (action == Which) {
        strncpy(commands->which, command, COMMAND_LENGTH);
    }
}

char* getCommand(Commands *commands, enum Action action) {
    if (action == Clean) {
        return commands->clean;
    } else if (action == Install) {
        return commands->install;
    } else if (action == Search) {
        return commands->search;
    } else if (action == SearchExact) {
        return commands->searchExact;
    } else if (action == Upgrade) {
        return commands->upgrade;
    } else if (action == Which) {
        return commands->which;
    }

    return "";
}
