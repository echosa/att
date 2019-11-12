#ifndef APT_H_
#define APT_H_

#include "commands.h"
#include "package_manager.h"
#include "requested_action.h"

static const char APT[] = "apt";

PackageManager* apt(RequestedAction* requestedAction);
Commands* getAptCommands(char* target);

#endif
