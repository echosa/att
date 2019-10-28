#include <stdio.h>
#include "flatpak.h"
#include "commands.h"

Commands* getFlatpakCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "flatpak install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "flatpak search %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "flatpak search %s", target);

    Commands* commands = commands_new();
    setCleanCommand(commands, "flatpak uninstall --unused");
    setInstallCommand(commands, installCommand);
    setSearchCommand(commands, searchCommand);
    setSearchExactCommand(commands, searchExactCommand);
    setUpgradeCommand(commands, "flatpak update");

    return commands;
}
