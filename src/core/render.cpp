#include "../render.hpp"
#include "../sortstack.hpp"










void drawRect(gfxData* g, int x, int y, int sx, int sy, int h, int w){
	SDL_Rect offset, clip;
	offset.x = x;
	offset.y = y;
	clip.x = sx;
	clip.y = sy;
	clip.h = h;
	clip.w = w;
	SDL_BlitSurface(g->tiles, &clip, g->screen, &offset);
}










void drawTile(gfxData* g, int x, int y, int t){
	int ty = (t / 8) * 24;
	int tx = (t % 8) * 16;
	drawRect(g, x, y, tx, ty, 24, 16);
}










int getFloorStateIndex(floorState s){
	switch(s){
		case WN: return 0; break;
		case NN: return 1; break;
		case WS: return 2; break;
		case NS: return 3; break;
	}
}










int getTileID(int t, floor f, int frame){
	frame = (frame / 4) % 2;
	switch(t){
		case  0: return 0; break;	//void
		case  1: return 2; break;	//floor
		case  2: return 1; break;	//wall
		case  4: return ( 8 + 8 * getFloorStateIndex(f.r)); break;	//red     tile
		case  5: return ( 9 + 8 * getFloorStateIndex(f.g)); break; //green   tile
		case  6: return (10 + 8 * getFloorStateIndex(f.b)); break;	//blue    tile
		case  8: return (40 + (isWalkable(f.r)? 8 : 0)); break;	//red     switch
		case  9: return (41 + (isWalkable(f.g)? 8 : 0)); break;	//green   switch
		case 10: return (42 + (isWalkable(f.b)? 8 : 0)); break;	//blue    switch
		case 11: return	14; break; //nonwalkable
		case 12: return (11 + 8 * getFloorStateIndex(f.m)); break;	//magenta tile
		case 13: return (12 + 8 * getFloorStateIndex(f.y)); break;  //yellow  tile
		case 14: return (13 + 8 * getFloorStateIndex(f.c)); break;	//cyan    tile
		case 16: return (43 + (isWalkable(f.m)? 8 : 0)); break;	//magenta switch
		case 17: return (44 + (isWalkable(f.y)? 8 : 0)); break;	//yellow  switch
		case 18: return (45 + (isWalkable(f.c)? 8 : 0)); break;  //cyan    switch
		case 19: return 15; break;  //nonpushable
		case 20: return 56 + (frame * 4); break;	//movement tiles
		case 21: return 57 + (frame * 4); break;	// 		"
		case 22: return 58 + (frame * 4); break;	// 		"
		case 23: return 59 + (frame * 4); break;	// 		"
		default: return 0; break;
	}
}










int getDepth(int t, floor f){
	switch(t){
		case  0: return 0; break;	//void
		case  1: return 0; break;	//floor
		case  2: return 2; break;	//wall
		case  4: return isWalkable(f.r)? 0 : 2; break;	//red     tile
		case  5: return isWalkable(f.g)? 0 : 2; break; //green   tile
		case  6: return isWalkable(f.b)? 0 : 2; break;	//blue    tile
		case  8: return 0; break;	//red     switch
		case  9: return 0; break;	//green   switch
		case 10: return 0; break;	//blue    switch
		case 11: return 0;	break; //nonwalkable
		case 12: return isWalkable(f.m)? 0 : 2; break;	//magenta tile
		case 13: return isWalkable(f.y)? 0 : 2; break; //yellow  tile
		case 14: return isWalkable(f.c)? 0 : 2; break;	//cyan    tile
		case 16: return 0; break;  //magenta switch
		case 17: return 0; break;  //yellow  switch
		case 18: return 0; break;  //cyan    switch
		case 19: return 0; break;  //nonpushable
		case 20: return 0; break;	//movement tiles
		case 21: return 0; break;	// 		"
		case 22: return 0; break;	// 		"
		case 23: return 0; break;	// 		"
		
		default: return 0; break;
	}
}










int maxX(puzzle* p){
	int mx = 0;
	for(int i = 0; i < 32; i++)
		for(int j = 0; j < 32; j++)
			if((p->tiles[i][j] != 0) && (i > mx)) mx = i;
	return mx;
}










int maxY(puzzle* p){
	int my = 0;
	for(int i = 0; i < 32; i++)
		for(int j = 0; j < 32; j++)
			if((p->tiles[i][j] != 0) && (j > my)) my = j;
	return my;
}









void render(gfxData* g, puzzle* p, int frame){
	sortstack s;
	
	//get offset to center puzzle. Not the best thing to do every frame, but who cares until it starts causing problems?
	int offx, offy;
	offx = 640 - (maxX(p) * 8);
	offy = 360 - (maxY(p) * 8);
	
	for(int i = 0; i < 32; i++){
		for(int j = 0; j < 32; j++){
			int depth = (j * 4) + getDepth(p->tiles[i][j], p->state);
			push(&s, Datum(getTileID(p->tiles[i][j], p->state, frame), depth, offx+(i*16),offy+(j*16)));
		}
	}
	int portalFrame = (frame / 8) % 4;
	int pdepth = ((p->py) / 16)+1;
	pdepth = ((pdepth) * 4) + 1;
	push(&s, Datum(4+portalFrame, (p->ey*4)+1, offx+(p->ex*16), offy+(p->ey*16)));	//entrance
	push(&s, Datum(4+portalFrame, (p->oy*4)+1, offx+(p->ox*16), offy+(p->oy*16)));	//exit
	push(&s, Datum(3, pdepth, offx+p->px, offy+p->py));	//player
	s = *sort(&s);
	for(int i = 0; i <= s.top; i++){
		datum d = s.data[i];
		drawTile(g, d.x, d.y, d.tile);
	}
	SDL_Flip(g->screen);
}




