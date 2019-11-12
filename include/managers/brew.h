#ifndef BREW_H_
#define BREW_H_

#include "commands.h"
#include "package_manager.h"
#include "requested_action.h"

static const char BREW[] = "brew";

PackageManager* brew(RequestedAction* requestedAction);
Commands* getBrewCommands(char* target);

#endif
