#ifndef COMMANDS_H_
#define COMMANDS_H_

#define COMMAND_LENGTH 100

typedef struct Commands Commands;

Commands* commands_new();
void setCleanCommand(Commands* commands, char command[]);
void setInstallCommand(Commands* commands, char command[]);
void setSearchCommand(Commands* commands, char command[]);
void setSearchExactCommand(Commands* commands, char command[]);
void setUpgradeCommand(Commands* commands, char command[]);
void setWhichCommand(Commands* commands, char command[]);
char* getCleanCommand(Commands* commands);
char* getInstallCommand(Commands* commands);
char* getSearchCommand(Commands* commands);
char* getSearchExactCommand(Commands* commands);
char* getUpgradeCommand(Commands* commands);
char* getWhichCommand(Commands* commands);

#endif
