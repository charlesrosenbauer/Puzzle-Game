#ifndef _DATA_HEADER
#define _DATA_HEADER


#include "SDL/SDL.h"










enum floorState{
	WS, NS, WN, NN
};










struct floor{
	floorState r, g, b, m, y, c;
};










struct puzzle{
	floor state;			//puzzle state
	uint8_t tiles [32][32];	//tile array
	float px, py;			//player coordinates
	int ex, ey, ox, oy;		//e -> entrance, o -> out
	int stepOn;				//floor tile beneath player
	int fx, fy;				//forced x, forced y
	int movementState = 0;	//movement state. At the moment, 0 = normal, 1 = forced
	int time = 0;
};










struct square{
	float x, y, h, w;
	bool solid = true;
};










bool isWalkable(floorState);
bool isSwitchable(floorState);
bool isSolid(int, floor, bool);
bool movePlayer(puzzle*, float, float);
floorState nextRGB(floorState);
floorState nextMYC(floorState);
bool isNewFloor(puzzle*);
void pressButton(puzzle*);
puzzle clearPuzzle();


#endif
