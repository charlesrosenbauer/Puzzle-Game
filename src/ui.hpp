#ifndef _UI_HEADER
#define _UI_HEADER


#include <string>
#include "core.hpp"










struct text{
	int x, y;
	std::string str = "";
};










void drawText(gfxData*, text);
text newText(int, int, std::string);



#endif
