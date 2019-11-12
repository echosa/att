#include <stdio.h>
#include "managers/brew.h"
#include "commands.h"

PackageManager* brew(RequestedAction* requestedAction) {
    return definePackageManager(BREW, getBrewCommands(getRequestedActionTarget(requestedAction)), getBrew(getRequestedActionManagers(requestedAction)));
}

Commands* getBrewCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "brew install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "brew search %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "brew search /^%s$/", target);

    Commands* commands = commands_new();
    setCommandString(commands, Clean, "brew cleanup");
    setCommandString(commands, Install, installCommand);
    setCommandString(commands, Search, searchCommand);
    setCommandString(commands, SearchExact, searchExactCommand);
    setCommandString(commands, Update, "brew update");
    setCommandString(commands, Upgrade, "brew update; brew upgrade");
    setCommandString(commands, Which, "which brew");

    return commands;
}
