#include "data.h"

extern ammos ammoArray[60];
extern tanks allTank[5];
extern int tankMap[35][60];
extern int ammoMap[35][60];
extern int gameLevel;

void initializeTank(bool isDualPlayer);
void tankMoveTest(bool gamePlay);
void keyProcess(int moveDirection, tanks *tank);
bool isBlocked(tanks tank);
bool fireAmmo(tanks tank);
void randomTankMove();
bool ammoIsHit();
void findFirstAvailableBirthPlace(bool isenemy);
