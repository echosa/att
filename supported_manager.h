#ifndef SUPPORTED_MANAGER_H_
#define SUPPORTED_MANAGER_H_

enum SupportedManager { Apt, Brew, Flatpak, Guix, Snap, InvalidManager };
static const int MANAGERS_COUNT = 5;

enum SupportedManager getManagerIndex(char* managerName);

#endif
