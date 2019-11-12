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
    setCommand(commands, Clean, "");
    setCommand(commands, Install, installCommand);
    setCommand(commands, Search, searchCommand);
    setCommand(commands, SearchExact, searchExactCommand);
    setCommand(commands, Upgrade, "sudo snap refresh");
    setCommand(commands, Which, "which snap");

    return commands;
}
