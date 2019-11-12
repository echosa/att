#include <stdio.h>
#include "../../include/managers/brew.h"
#include "../../include/commands.h"

Commands* getBrewCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "brew install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "brew search %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "brew search /^%s$/", target);

    Commands* commands = commands_new();
    setCommand(commands, Clean, "brew cleanup");
    setCommand(commands, Install, installCommand);
    setCommand(commands, Search, searchCommand);
    setCommand(commands, SearchExact, searchExactCommand);
    setCommand(commands, Upgrade, "brew update; brew upgrade");
    setCommand(commands, Which, "which brew");

    return commands;
}
