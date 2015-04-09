#include "data.h"

extern tanks player1;
extern tanks player2;
extern ammos ammoArray[60];
extern tanks enemyTank[3];

void initializeTank();
void tankMoveTest();
void keyProcess(int moveDirection, tanks *tank);
bool isBlocked(tanks tank);
bool fireAmmo(tanks tank);
void randomTankMove();