#ifndef ACTION_H_
#define ACTION_H_

#include <stdbool.h>

enum Action { Clean, Install, Search, SearchExact, Upgrade, Help, InvalidAction };

static const char CLEAN_ACTION[] = "clean";
static const char INSTALL_ACTION[] = "install";
static const char SEARCH_ACTION[] = "search";
static const char UPGRADE_ACTION[] = "upgrade";

enum Action parseAction(char* action, bool exactSearch);

#endif
