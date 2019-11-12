#ifndef FLATPAK_H_
#define FLATPAK_H_

#include "commands.h"
#include "package_manager.h"
#include "requested_action.h"

static const char FLATPAK[] = "flatpak";

PackageManager* flatpak(RequestedAction* requestedAction);
Commands* getFlatpakCommands(char* target);

#endif
