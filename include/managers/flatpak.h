#ifndef FLATPAK_H_
#define FLATPAK_H_

#include "../commands.h"

static const char FLATPAK[] = "flatpak";

Commands* getFlatpakCommands(char* target);

#endif
