#ifndef _RENDER_HEADER
#define _RENDER_HEADER


#include "data.hpp"










struct gfxData{
	SDL_Surface* screen = nullptr;
	SDL_Surface* tiles  = nullptr;
	SDL_Surface* font   = nullptr;
};










void render(gfxData*, puzzle*, int);
void drawTile(gfxData*, int, int, int);
int getTileID(int, floor, int);



#endif
