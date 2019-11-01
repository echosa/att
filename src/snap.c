#include <stdio.h>
#include "../include/snap.h"
#include "../include/commands.h"

Commands* getSnapCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "snap install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "snap find %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "snap find %s", target);

    Commands* commands = commands_new();
    setCleanCommand(commands, "");
    setInstallCommand(commands, installCommand);
    setSearchCommand(commands, searchCommand);
    setSearchExactCommand(commands, searchExactCommand);
    setUpgradeCommand(commands, "sudo snap refresh");

    return commands;
}
