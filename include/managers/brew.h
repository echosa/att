#ifndef BREW_H_
#define BREW_H_

#include "commands.h"

static const char BREW[] = "brew";

Commands* getBrewCommands(char* target);

#endif
