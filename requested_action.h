#ifndef REQUESTED_ACTION_H_
#define REQUESTED_ACTION_H_

#include <stdbool.h>
#include "managers.h"
#include "action.h"

typedef struct RequestedAction RequestedAction;

RequestedAction* requested_action_new();

Managers* getRequestedActionManagers(RequestedAction* requestedAction);
void setRequestedActionManagers(RequestedAction* requestedAction, Managers* managers);
enum Action getRequestedActionAction(RequestedAction* requestedAction);
void setRequestedActionAction(RequestedAction* requestedAction, enum Action action);
char* getRequestedActionTarget(RequestedAction* requestedAction);
void setRequestedActionTarget(RequestedAction* requestedAction, char* target);
bool isDebug(RequestedAction* requestedAction);
void enableDebug(RequestedAction* requestedAction);
bool isExactSearch(RequestedAction* requestedAction);
void enableExactSearch(RequestedAction* requestedAction);
void enableManagerForRequestedAction(RequestedAction* requestedAction, char* managerName);

#endif
