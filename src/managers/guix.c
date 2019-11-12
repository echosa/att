#include <stdio.h>
#include "managers/guix.h"
#include "commands.h"

PackageManager* guix(RequestedAction* requestedAction) {
    return definePackageManager(GUIX, getGuixCommands(getRequestedActionTarget(requestedAction)), getGuix(getRequestedActionManagers(requestedAction)));
}

Commands* getGuixCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "guix install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "guix package -A %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "guix package -A ^%s$", target);

    Commands* commands = commands_new();
    setCommandString(commands, Clean, "guix package --delete-generations; guix gc --collect-garbage; guix gc --list-dead");
    setCommandString(commands, Install, installCommand);
    setCommandString(commands, Search, searchCommand);
    setCommandString(commands, SearchExact, searchExactCommand);
    setCommandString(commands, Update, "guix pull");
    setCommandString(commands, Upgrade, "guix package -u");
    setCommandString(commands, Which, "which guix");

    return commands;
}
