#include <stdio.h>
#include "../include/flatpak.h"
#include "../include/commands.h"

Commands* getFlatpakCommands(char* target) {
    char installCommand[COMMAND_LENGTH];
    snprintf(installCommand, COMMAND_LENGTH, "flatpak install %s", target);
    char searchCommand[COMMAND_LENGTH];
    snprintf(searchCommand, COMMAND_LENGTH, "flatpak search %s", target);
    char searchExactCommand[COMMAND_LENGTH];
    snprintf(searchExactCommand, COMMAND_LENGTH, "flatpak search %s", target);

    Commands* commands = commands_new();
    setCommand(commands, Clean, "flatpak uninstall --unused");
    setCommand(commands, Install, installCommand);
    setCommand(commands, Search, searchCommand);
    setCommand(commands, SearchExact, searchExactCommand);
    setCommand(commands, Upgrade, "flatpak update");
    setCommand(commands, Which, "which flatpak");

    return commands;
}
