#ifndef SUPPORTED_MANAGER_H_
#define SUPPORTED_MANAGER_H_

#include "package_manager.h"
#include "requested_action.h"

enum SupportedManager { Apt, Brew, Flatpak, Guix, Snap, InvalidManager };
static const int MANAGERS_COUNT = 5;

enum SupportedManager getManagerIndex(char* managerName);
PackageManager* apt(RequestedAction* requestedAction);
PackageManager* brew(RequestedAction* requestedAction);
PackageManager* flatpak(RequestedAction* requestedAction);
PackageManager* guix(RequestedAction* requestedAction);
PackageManager* snap(RequestedAction* requestedAction);

#endif
