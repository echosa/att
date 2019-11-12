#include <stdio.h>
#include "../include/brew.h"
#include "../include/commands.h"

Commands* getBrewCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "brew install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "brew search %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "brew search /^%s$/", target);

    Commands* commands = commands_new();
    setCleanCommand(commands, "brew cleanup");
    setInstallCommand(commands, installCommand);
    setSearchCommand(commands, searchCommand);
    setSearchExactCommand(commands, searchExactCommand);
    setUpgradeCommand(commands, "brew update; brew upgrade");
    setWhichCommand(commands, "which brew");

    return commands;
}
