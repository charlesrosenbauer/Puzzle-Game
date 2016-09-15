#include "../core.hpp"
#include "../ui.hpp"






#include <iostream>



int mainloop(gfxData* g, puzzle* p){

	Uint8* keystates = SDL_GetKeyState(0);
	p->px = 16 * p->ex;
	p->py = 16 * p->ey;
	float px = 0, py = 0;
	int ret = 1;
	int iter = 0;
	while(ret == 1){
		
		px = 0, py = 0;
		SDL_FillRect(g->screen, 0, 0);
	
		SDL_Event event;
		while(SDL_PollEvent( &event )){
			if(event.type == SDL_QUIT) ret = -1;
		}
		if(keystates[SDLK_UP   ]) py += -1;
		if(keystates[SDLK_DOWN ]) py +=  1;
		if(keystates[SDLK_RIGHT]) px +=  1;
		if(keystates[SDLK_LEFT ]) px += -1;
		if(keystates[SDLK_w]) py += -1;
		if(keystates[SDLK_s]) py +=  1;
		if(keystates[SDLK_d]) px +=  1;
		if(keystates[SDLK_a]) px += -1;
		
		if(!movePlayer(p, px * 0.7, py * 0.7))
			if(!movePlayer(p, px * 0.7, 0))
				movePlayer(p, 0, py * 0.7);
				
	    int ix = (p->px + 8) / 16;
	    int iy = (p->py + 8) / 16;
		if((ix == p->ox) && (iy == p->oy))
		    ret = 0;        //update this later
				
		if(isNewFloor(p)) pressButton(p);
		render(g, p, iter);
		
		SDL_Delay(16);
		iter++;
	}
	SDL_Delay(50);
	SDL_FillRect(g->screen, 0, 0);
	SDL_Flip(g->screen);
	SDL_Delay(250);
	return ret;
}










int editloop(gfxData* g, puzzle* p){

	Uint8* keystates = SDL_GetKeyState(0);
	float px = 0, py = 0;
	int ret = 1;
	int iter = 0;
	int tile = 0;
	text texts[7];
	texts[0] = newText(16, 320, "DIRECTION OR WASD TO MOVE");
	texts[1] = newText(16, 336, "E TO SET ENTRANCE POINT");
	texts[2] = newText(16, 352, "O TO SET EXIT POINT");
	texts[3] = newText(16, 368, "< AND > TO CHANGE TILE");
	texts[4] = newText(16, 384, "SPACE TO SET TILE");
	texts[5] = newText(16, 400, "HOLD CTRL FOR PLAYER PHYSICS");
	texts[6] = newText(16, 416, "X TO EXIT AND EXPORT LEVEL");
	
	while(ret == 1){
		
		px = 0, py = 0;
		SDL_FillRect(g->screen, 0, 0);
		
		int ix = (p->px+8) / 16;
		int iy = (p->py+8) / 16;
		
	
		SDL_Event event;
		while(SDL_PollEvent( &event )){
			if(event.type == SDL_QUIT) ret = -1;
			if(event.type == SDL_KEYDOWN){
				if(keystates[SDLK_LSHIFT] || keystates[SDLK_RSHIFT]){
					if(event.key.keysym.sym == SDLK_COMMA ) tile = (tile + 23) % 24;
					if(event.key.keysym.sym == SDLK_PERIOD) tile = (tile + 25) % 24;
				}
				if(event.key.keysym.sym == SDLK_e) { p->ex = ix; p->ey = iy; }
				if(event.key.keysym.sym == SDLK_o) { p->ox = ix; p->oy = iy; }
				if(event.key.keysym.sym == SDLK_x) ret = 0;
			}
		}
		if(keystates[SDLK_SPACE]) p->tiles[ix][iy] = tile;
		if(keystates[SDLK_UP   ]) py += -1;
		if(keystates[SDLK_DOWN ]) py +=  1;
		if(keystates[SDLK_RIGHT]) px +=  1;
		if(keystates[SDLK_LEFT ]) px += -1;
		if(keystates[SDLK_w]) py += -1;
		if(keystates[SDLK_s]) py +=  1;
		if(keystates[SDLK_d]) px +=  1;
		if(keystates[SDLK_a]) px += -1;
		if(keystates[SDLK_LCTRL] || keystates[SDLK_RCTRL]){
			if(!movePlayer(p, px * 0.7, py * 0.7))
				if(!movePlayer(p, px * 0.7, 0))
					movePlayer(p, 0, py * 0.7);
		}else{
			p->px += px;
			p->py += py;
			p->movementState = 0;
		}
				
		if(isNewFloor(p)) pressButton(p);
		drawTile(g, 0, 0, getTileID(tile, p->state, iter));
		for(int i = 0; i < 7; i++) drawText(g, texts[i]);
		render(g, p, iter);
		
		SDL_Delay(16);
		iter++;
	}
	return ret;
}










int endloop(gfxData* g){
    //This is an ending message. It may change at some point.
    text texts[16];
    SDL_FillRect(g->screen, 0, 0);
	texts[ 0] = newText(16,  16, "THANK YOU FOR TESTING THE GAME AS IT IS.");
    for(int i = 0; i < 1; i++) drawText(g, texts[i]);
    
    SDL_Flip(g->screen);
    int ret = 1;
	while(ret == 1){
		SDL_Event event;
		while(SDL_PollEvent( &event )){
			if(event.type == SDL_QUIT) ret = -1;
		}

	}
	return ret;
}









