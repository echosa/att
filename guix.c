#include <stdio.h>
#include "guix.h"
#include "commands.h"

Commands* getGuixCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "guix install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "guix package -A %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "guix package -A ^%s$", target);

    Commands* commands = commands_new();
    setCleanCommand(commands, "guix package --delete-generations; guix gc --collect-garbage; guix gc --list-dead");
    setInstallCommand(commands, installCommand);
    setSearchCommand(commands, searchCommand);
    setSearchExactCommand(commands, searchExactCommand);
    setUpgradeCommand(commands, "guix pull; guix package -u");

    return commands;
}
