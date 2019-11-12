#ifndef SNAP_H_
#define SNAP_H_

#include "commands.h"
#include "package_manager.h"
#include "requested_action.h"

static const char SNAP[] = "snap";

PackageManager* snap(RequestedAction* requestedAction);
Commands* getSnapCommands(char* target);

#endif
