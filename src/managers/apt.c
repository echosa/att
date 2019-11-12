#include <stdio.h>
#include "managers/apt.h"
#include "commands.h"

PackageManager* apt(RequestedAction* requestedAction) {
    return definePackageManager(APT, getAptCommands(getRequestedActionTarget(requestedAction)), getApt(getRequestedActionManagers(requestedAction)));
}

Commands* getAptCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "sudo apt install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "apt search %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "apt search ^%s$", target);

    Commands* commands = commands_new();
    setCommandString(commands, Clean, "sudo apt autoremove");
    setCommandString(commands, Install, installCommand);
    setCommandString(commands, Search, searchCommand);
    setCommandString(commands, SearchExact, searchExactCommand);
    setCommandString(commands, Update, "sudo apt update");
    setCommandString(commands, Upgrade, "sudo apt update; sudo apt upgrade");
    setCommandString(commands, Which, "which apt");

    return commands;
}
