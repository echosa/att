#include <stdio.h>
#include "managers/snap.h"
#include "commands.h"

Commands* getSnapCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "snap install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "snap find %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "snap find %s", target);

    Commands* commands = commands_new();
    setCommandString(commands, Clean, "");
    setCommandString(commands, Install, installCommand);
    setCommandString(commands, Search, searchCommand);
    setCommandString(commands, SearchExact, searchExactCommand);
    setCommandString(commands, Upgrade, "sudo snap refresh");
    setCommandString(commands, Which, "which snap");

    return commands;
}
