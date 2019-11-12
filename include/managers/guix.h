#ifndef GUIX_H_
#define GUIX_H_

#include "commands.h"
#include "package_manager.h"
#include "requested_action.h"

static const char GUIX[] = "guix";

PackageManager* guix(RequestedAction* requestedAction);
Commands* getGuixCommands(char* target);

#endif
