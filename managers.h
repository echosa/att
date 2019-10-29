#ifndef MANAGERS_H_
#define MANAGERS_H_

typedef struct Managers Managers;

Managers* managers_new();
void setAllManagers(Managers* managers, bool enabled);
void setApt(Managers* managers, bool enabled);
void setBrew(Managers* managers, bool enabled);
void setFlatpak(Managers* managers, bool enabled);
void setGuix(Managers* managers, bool enabled);
void setSnap(Managers* managers, bool enabled);
bool getApt(Managers* managers);
bool getBrew(Managers* managers);
bool getFlatpak(Managers* managers);
bool getGuix(Managers* managers);
bool getSnap(Managers* managers);

#endif
