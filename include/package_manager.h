#ifndef PACKAGE_MANAGER_H_
#define PACKAGE_MANAGER_H_

#include <stdbool.h>
#include "commands.h"

#define NAME_LENGTH 10

typedef struct PackageManager PackageManager;

PackageManager* definePackageManager(const char name[], Commands* commands, bool enabled);
char* getPackageManagerName(PackageManager* packageManager);
Commands* getPackageManagerCommands(PackageManager* packageManager);
void setPackageManagerInstallCommand(PackageManager* packageManager, Commands* commands);
bool isPackageManagerEnabled(PackageManager* packageManager);

#endif
