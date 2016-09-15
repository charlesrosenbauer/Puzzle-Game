#ifndef _CORE_HEADER
#define _CORE_HEADER


#include "data.hpp"
#include "render.hpp"
#include <string>










int mainloop(gfxData*, puzzle*);
int editloop(gfxData*, puzzle*);
int endloop(gfxData*);










bool importPuzzle(puzzle*, std::string);
bool exportPuzzle(puzzle*, std::string);





#endif
