#ifndef RUN_H_
#define RUN_H_

#include "package_manager.h"
#include "requested_action.h"

void executeAction(PackageManager* managers[], RequestedAction* requestedAction);
    
#endif
