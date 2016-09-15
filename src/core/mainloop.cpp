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

    text texts[16];
    SDL_FillRect(g->screen, 0, 0);
	texts[ 0] = newText(16,  16, "THANK YOU FOR TESTING THE GAME AS IT IS. IT IS STILL IN EARLY DEVELOPMENT AND IS LIKELY TO CHANGE SIGNIFICANTLY.");
	texts[ 1] = newText(16,  32, "BY GIVING FEEDBACK, YOU ARE MAKING SURE THAT THOSE CHANGES IMPROVE THE GAME AS MUCH AS POSSIBLE.");
	texts[ 2] = newText(16,  48, "I WOULD GREATLY APPRECIATE IT IF YOU WOULD TAKE THE TIME TO PROVIDE SOME FEEDBACK. YOU MAY EMAIL IT TO CHARLES.ROSENBAUER@GMAIL.COM.");
	texts[ 3] = newText(16,  80, "THE FOLLOWING ARE QUESTIONS THAT WOULD HELP ME SIGNIFICANTLY IF YOU ANSWERED THEM IN YOUR EMAIL:");
	texts[ 4] = newText(16,  96, "1. WHAT DID YOU THINK OF THE GAMEPLAY? WHAT DID YOU LIKE ABOUT THE PUZZLES? WHAT DID YOU NOT LIKE?");
	texts[ 5] = newText(16, 112, "2. ABOUT HOW LONG DID IT TAKE YOU TO BEAT THE GAME?");
	texts[ 6] = newText(16, 128, "3. WHAT DO YOU THINK OF THE GAMES GRAPHICS?");
	texts[ 7] = newText(16, 144, "4. WHAT OPERATING SYSTEM ARE YOU PLAYING THIS GAME ON? WINDOWS? LINUX? OTHER?");
	texts[ 8] = newText(16, 160, "5. DID YOU HAVE ANY PERFORMANCE ISSUES? IF SO, PLEASE PROVIDE ANY INFORMATION YOU CAN ON YOUR COMPUTERS HARDWARE.");
	texts[ 9] = newText(16, 176, "6. OVERALL, DID YOU LIKE THE GAME? WHY OR WHY NOT?");
	texts[10] = newText(16, 192, "7. HOW MUCH WOULD YOU PAY FOR A LONGER AND MORE POLISHED VERSION OF THE GAME?");
	texts[11] = newText(16, 208, "8. ANY OTHER COMMENTS, FEEDBACK, OR SUGGESTIONS?");
	texts[12] = newText(16, 240, "ONCE AGAIN, THANK YOU FOR PLAYTESTING THE GAME. I GREATLY APPRECIATE ANY FEEDBACK, POSITIVE OR NEGATIVE. JUST KEEP IT CONSTRUCTIVE.");
	//texts[13] = newText(16, 256, "3. WHAT DO YOU THINK OF THE GAMES GRAPHICS?");
    for(int i = 0; i < 13; i++) drawText(g, texts[i]);
    
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









