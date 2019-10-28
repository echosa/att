#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>
#include <string.h>

enum Action { Clean, Install, Search, SearchExact, Upgrade, Help, InvalidAction };
static const char CLEAN_ACTION[] = "clean";
static const char INSTALL_ACTION[] = "install";
static const char SEARCH_ACTION[] = "search";
static const char UPGRADE_ACTION[] = "upgrade";

enum Action parseAction(char* action, bool exactSearch) {
    if (strcmp(action, CLEAN_ACTION) == 0) {
        return Clean;
    } else if (strcmp(action, INSTALL_ACTION) == 0) {
        return Install;
    } else if (strcmp(action, SEARCH_ACTION) == 0) {
        return exactSearch ? SearchExact : Search;
    } else if (strcmp(action, UPGRADE_ACTION) == 0) {
        return Upgrade;
    } else {
        return InvalidAction;
    }
}

#endif
