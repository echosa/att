#include <stdio.h>
#include "apt.h"
#include "commands.h"

Commands* getAptCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "sudo apt install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "apt search %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "apt search ^%s$", target);

    Commands* commands = commands_new();
    setCleanCommand(commands, "sudo apt autoremove");
    setInstallCommand(commands, installCommand);
    setSearchCommand(commands, searchCommand);
    setSearchExactCommand(commands, searchExactCommand);
    setUpgradeCommand(commands, "sudo apt update; sudo apt upgrade");

    return commands;
}
