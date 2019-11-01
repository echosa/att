#include <string.h>
#include "../include/action.h"

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
