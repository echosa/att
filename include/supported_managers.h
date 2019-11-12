#ifndef SUPPORTED_MANAGERS_H_
#define SUPPORTED_MANAGERS_H_

#include "managers/apt.h"
#include "managers/brew.h"
#include "managers/flatpak.h"
#include "managers/guix.h"
#include "managers/snap.h"

enum SupportedManager { Apt, Brew, Flatpak, Guix, Snap, InvalidManager };
static const int MANAGERS_COUNT = 5;

enum SupportedManager getManagerIndex(char* managerName);

#endif
