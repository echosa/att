#ifndef PACKAGE_MANAGER_H_
#define PACKAGE_MANAGER_H_

#include <stdbool.h>
#include "commands.h"

#define NAME_LENGTH 10
#define INSTALL_CHECK_LENGTH 50

typedef struct PackageManager PackageManager;

PackageManager* definePackageManager(const char name[], Commands* commands, bool enabled);
bool isPackageManagerInstalled(PackageManager* manager);
char* getPackageManagerName(PackageManager* manager);
char* getPackageManagerCommand(PackageManager* manager, enum Action action);
void setPackageManagerInstallCommand(PackageManager* manager, Commands* commands);
bool isPackageManagerEnabled(PackageManager* manager);

#endif
