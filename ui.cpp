#include "../ui.hpp"










void drawSymbol(gfxData* g, int x, int y, int sx, int sy){
	SDL_Rect offset, clip;
	offset.x = x;
	offset.y = y;
	clip.x = sx;
	clip.y = sy;
	clip.h = 12;
	clip.w = 8;
	SDL_BlitSurface(g->font, &clip, g->screen, &offset);
}










void drawChar(gfxData* g, int x, int y, char c){
	int t = 0;
	if((c > 64) && (c < 91)){
		t = c-65;
	}else if((c > 47) && (c < 58)){
		t = c-22;
	}else{
		switch(c){
			case '.': t = 36; break;
			case ',': t = 37; break;
			case '>': t = 38; break;
			case '<': t = 39; break;
			case ':': t = 40; break;
			case '@': t = 41; break;
			case '?': t = 42; break;
			case ' ': t = 43; break;
		}
	} 
	int ty = (t / 8) * 12;
	int tx = (t % 8) * 8;
	drawSymbol(g, x, y, tx, ty);
}










void drawText(gfxData* g, text t){
	for(int i = 0; i < t.str.size(); i++)
		drawChar(g, t.x+(8*i), t.y, t.str[i]);
}










text newText(int x, int y, std::string str){
	text t;
	t.x = x;
	t.y = y;
	t.str = str;
	return t;
}
