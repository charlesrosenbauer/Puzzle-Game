#include "../data.hpp"










bool isWalkable(floorState s){
	switch(s){
		case WN: return true ; break;
		case NN: return false; break;
		case WS: return true ; break;
		case NS: return false; break;
	}
}










bool isSwitchable(floorState s){
	switch(s){
		case WN: return false; break;
		case NN: return false; break;
		case WS: return true ; break;
		case NS: return true ; break;
	}
}










bool isSolid(int t, floor f, bool isForced){
	switch(t){
		case  0: return true;  break;	//void
		case  1: return false; break;	//floor
		case  2: return true;  break;	//wall
		case  4: return !isWalkable(f.r); break;	//red     tile
		case  5: return !isWalkable(f.g); break; //green   tile
		case  6: return !isWalkable(f.b); break;	//blue    tile
		case  8: return false; break;	//red     switch
		case  9: return false; break;	//green   switch
		case 10: return false; break;	//blue    switch
		case 11: return !isForced; break;  //onlywalkable
		case 12: return !isWalkable(f.m); break;	//magenta tile
		case 13: return !isWalkable(f.y); break; //yellow  tile
		case 14: return !isWalkable(f.c); break;	//cyan    tile
		case 16: return false; break;  //magenta switch
		case 17: return false; break;  //yellow  switch
		case 18: return false; break;  //cyan    switch
		case 19: return isForced; break;  //onlypushable
		case 20: return false; break;	//movement tiles
		case 21: return false; break;	// 		"
		case 22: return false; break;	// 		"
		case 23: return false; break;	// 		"
		
		default: return true; break;
	}
}










bool isCollided(square a, square b){
	float amx = a.x + a.w;
	float amy = a.y + a.h;
	float bmx = b.x + b.w;
	float bmy = b.y + b.h;
	return b.solid && ((a.x < bmx) && (a.y < bmy) && (b.x < amx) && (b.y < bmy));
}










bool movingApart(float x, float y, float dx, float dy, square s){
	float tx = x + dx;
	float ty = y + dy;
	float ax = s.x - tx;
	float ay = s.y - ty;
	float bx = s.x - x;
	float by = s.y - y;
	return ((ax * ax) + (ay * ay)) > ((bx * bx) + (by * by));
}










int getTile(puzzle* p, int x, int y){
	return ((x < 0) || (y < 0) || (x > 31) || (y > 31))? 0 : p->tiles[x][y];
}










bool movePlayer(puzzle* p, float dx, float dy){
	if(p->movementState == 1){
		dx = p->fx;
		dy = p->fy;
	}

	square sqr[3][3];
	int pix = (p->px + dx) / 16;
	int piy = (p->py + dy) / 16;
	float px = (p->px + dx);
	float py = (p->py + dy);
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			sqr[i][j].solid = isSolid(getTile(p, pix+i-1, piy+j-1), p->state, p->movementState == 1);
			sqr[i][j].h = 16;
			sqr[i][j].w = 16;
			sqr[i][j].x = 16 * (pix+i-1);
			sqr[i][j].y = 16 * (piy+j-1);
		}
	}
	square ps;
	ps.h = 12;
	ps.w = 12;
	ps.x = px+2;
	ps.y = py+2;
	bool c = false;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			c = c || (isCollided(ps, sqr[i][j]) && !movingApart(p->px, p->py, dx, dy, sqr[i][j]));
	if(!c){
		p->px += dx;
		p->py += dy;
		return true;
	}
	//collision has occurred
	p->movementState = 0;
	return false;
}










floorState nextRGB(floorState x){
	switch(x){
		case WN: return NN;
		case NN: return WS;
		case WS: return NS;
		case NS: return WN;
	}
}










floorState nextMYC(floorState x){
	switch(x){
		case WN: return WS;
		case NN: return WN;
		case WS: return NS;
		case NS: return NN;
	}
}










bool isNewFloor(puzzle* p){
	int ix = (p->px + 8) / 16;
	int iy = (p->py + 8) / 16;
	if(p->tiles[ix][iy] != p->stepOn){
		p->stepOn = p->tiles[ix][iy];
		return true;
	}
	return false;
}










void pressButton(puzzle* p){
	switch(p->stepOn){
		case  4: if(isSwitchable(p->state.r)) p->state.g = nextRGB(p->state.g), p->state.b = nextRGB(p->state.b); break; //red     tile
		case  5: if(isSwitchable(p->state.g)) p->state.r = nextRGB(p->state.r), p->state.b = nextRGB(p->state.b); break; //green   tile
		case  6: if(isSwitchable(p->state.b)) p->state.r = nextRGB(p->state.r), p->state.g = nextRGB(p->state.g); break; //blue    tile
		case  8: p->state.r = nextRGB(p->state.r); break;	//red     switch --
		case  9: p->state.g = nextRGB(p->state.g); break;	//green   switch --
		case 10: p->state.b = nextRGB(p->state.b); break;	//blue    switch --
		//case 11: return (42 + isWalkable? 8 : 0);			 break; //simple  switch
		case 12: if(isSwitchable(p->state.m)) p->state.y = nextMYC(p->state.y), p->state.c = nextMYC(p->state.c); break;	//magenta tile
		case 13: if(isSwitchable(p->state.y)) p->state.m = nextMYC(p->state.m), p->state.c = nextMYC(p->state.c); break; //yellow  tile
		case 14: if(isSwitchable(p->state.c)) p->state.m = nextMYC(p->state.m), p->state.y = nextMYC(p->state.y); break;	//cyan    tile
		case 16: p->state.m = nextMYC(p->state.m); break;	//magenta switch --
		case 17: p->state.y = nextMYC(p->state.y); break;	//yellow  switch --
		case 18: p->state.c = nextMYC(p->state.c); break; //cyan    switch --
		//case 11: return (42 + isWalkable? 8 : 0);			 break; //complex switch
		case 20: if(p->movementState != 1){p->movementState = 1; p->fx =  0; p->fy = -2;} break;
		case 21: if(p->movementState != 1){p->movementState = 1; p->fx =  2; p->fy =  0;} break;
		case 22: if(p->movementState != 1){p->movementState = 1; p->fx =  0; p->fy =  2;} break;
		case 23: if(p->movementState != 1){p->movementState = 1; p->fx = -2; p->fy =  0;} break;
	}
}










puzzle clearPuzzle(){
	puzzle p;
	for(int i = 0; i < 32; i++)
		for(int j = 0; j < 32; j++)
			p.tiles[i][j] = 0;
	p.state.r = WN;
	p.state.g = WN;
	p.state.b = WN;
	p.state.m = WN;
	p.state.y = WN;
	p.state.c = WN;
	p.ex = 0;
	p.ey = 0;
	p.ox = 0;
	p.oy = 0;
	p.px = 0;
	p.py = 0;
	return p;
}













