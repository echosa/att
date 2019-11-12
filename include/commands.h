#ifndef COMMANDS_H_
#define COMMANDS_H_

#define COMMAND_LENGTH 100

#include "action.h"

typedef struct Commands Commands;

Commands* commands_new();
void setCommand(Commands* commands, enum Action action, char command[]);
char* getCommandString(Commands* commands, enum Action action);

#endif
