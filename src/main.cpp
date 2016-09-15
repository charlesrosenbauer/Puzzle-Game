#include "../core.hpp"
#include <iostream>









int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("Puzzle Test", 0);
	SDL_Surface* screen = SDL_SetVideoMode(1280, 720, 32, 0);
	SDL_Surface* tiles  = SDL_LoadBMP("data/tileset.bmp");
	SDL_SetColorKey(tiles, SDL_SRCCOLORKEY, 0xFFFFFF);
	SDL_Surface* font   = SDL_LoadBMP("data/font.bmp");
	SDL_SetColorKey(font,  SDL_SRCCOLORKEY, 0xFFFFFF);
	
	gfxData g;
	g.screen = screen;
	g.tiles  = tiles;
	g.font   = font;
	
	puzzle p[16];
	for(int i = 0; i < 16; i++) p[i] = clearPuzzle();
	
	
	importPuzzle(&p[ 0], "puzzles/0.puzl");
    importPuzzle(&p[ 1], "puzzles/1.puzl");
    importPuzzle(&p[ 2], "puzzles/2.puzl");
    importPuzzle(&p[ 3], "puzzles/3.puzl");
    importPuzzle(&p[ 4], "puzzles/4.puzl");
    importPuzzle(&p[ 5], "puzzles/5.puzl");
    importPuzzle(&p[ 6], "puzzles/6.puzl");
    importPuzzle(&p[ 7], "puzzles/7.puzl");
    importPuzzle(&p[ 8], "puzzles/8.puzl");
    importPuzzle(&p[ 9], "puzzles/9.puzl");
    
    int state = 1;
    int room = 0;
    while(state != -1){
        state = mainloop(&g, &p[room]);
        room++;
        state = (room > 10)? -1 : state;
    }
    
    endloop(&g);

	
	/*
	//THIS CODE IS USED FOR EDITING LEVELS
	editloop(&g, &p[ 8]);
	exportPuzzle(&p[ 8], "puzzles/8.puzl");
	editloop(&g, &p[ 9]);
    exportPuzzle(&p[ 9], "puzzles/9.puzl");
    editloop(&g, &p[10]);
	exportPuzzle(&p[10], "puzzles/10.puzl");
	editloop(&g, &p[11]);
    exportPuzzle(&p[11], "puzzles/11.puzl");
    */
	SDL_Quit();
}
