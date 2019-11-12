#include <stdio.h>
#include "../include/guix.h"
#include "../include/commands.h"

Commands* getGuixCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "guix install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "guix package -A %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "guix package -A ^%s$", target);

    Commands* commands = commands_new();
    setCommand(commands, Clean, "guix package --delete-generations; guix gc --collect-garbage; guix gc --list-dead");
    setCommand(commands, Install, installCommand);
    setCommand(commands, Search, searchCommand);
    setCommand(commands, SearchExact, searchExactCommand);
    setCommand(commands, Upgrade, "guix pull; guix package -u");
    setCommand(commands, Which, "which guix");

    return commands;
}
