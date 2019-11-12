#include <stdio.h>
#include "../../include/managers/apt.h"
#include "../../include/commands.h"

Commands* getAptCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "sudo apt install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "apt search %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "apt search ^%s$", target);

    Commands* commands = commands_new();
    setCommand(commands, Clean, "sudo apt autoremove");
    setCommand(commands, Install, installCommand);
    setCommand(commands, Search, searchCommand);
    setCommand(commands, SearchExact, searchExactCommand);
    setCommand(commands, Upgrade, "sudo apt update; sudo apt upgrade");
    setCommand(commands, Which, "which apt");

    return commands;
}
