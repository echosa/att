#include <stdio.h>
#include "managers/flatpak.h"
#include "commands.h"

Commands* getFlatpakCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "flatpak install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "flatpak search %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "flatpak search %s", target);

    Commands* commands = commands_new();
    setCommandString(commands, Clean, "flatpak uninstall --unused");
    setCommandString(commands, Install, installCommand);
    setCommandString(commands, Search, searchCommand);
    setCommandString(commands, SearchExact, searchExactCommand);
    setCommandString(commands, Upgrade, "flatpak update");
    setCommandString(commands, Which, "which flatpak");

    return commands;
}
