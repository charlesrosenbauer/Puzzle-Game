#include "../core.hpp"
#include <fstream>
#include <iostream>










floorState createFloorState(int x){
	x %= 4;
	switch(x){
		case 0: return WN;
		case 1: return NN;
		case 2: return WS;
		case 3: return NS;
	}
}










int getFloorStateID(floorState s){
    switch(s){
        case WN: return 0;
        case NN: return 1;
        case WS: return 2;
        case NS: return 3;
    }
}










bool importPuzzle(puzzle* p, std::string filename){
	char* buffer = nullptr;
	std::ifstream file(filename, std::ios::binary);
	
	if(file.is_open()){
	    file.seekg(0, std::ios::end);
		int size = file.tellg();
		buffer = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();
		
		if(size < 1056){
			std::cout << "INVALID FILE SIZE: " << filename << "!!" << size << "\n";
			delete [] buffer;
			return false;
		}
		std::string hdr = "SWTXBORD";
		bool c = true;
		for(int i = 0; i < 8; i++)
			c = c && (hdr[i] == buffer[i]);
		
		if(!c){
			std::cout << "INVALID FILE HEADER: " << filename << "!!\n";
			delete [] buffer;
			return false;
		}
		
		//initialize header of new puzzle
		p->time    = (buffer[0x10] << 8) | buffer[0x11];
		p->state.r = createFloorState(buffer[0x12]);
		p->state.g = createFloorState(buffer[0x13]);
		p->state.b = createFloorState(buffer[0x14]);
		p->state.m = createFloorState(buffer[0x15]);
		p->state.y = createFloorState(buffer[0x16]);
		p->state.c = createFloorState(buffer[0x17]);
		p->ex = buffer[0x18] % 32;
		p->ey = buffer[0x19] % 32;
		p->ox = buffer[0x1A] % 32;
		p->oy = buffer[0x1B] % 32;
		p->px = 16 * p->ex;
		p->py = 16 * p->ey;
		p->fx = 0;
		p->fy = 0;
		p->stepOn = 0;
		p->movementState = 0;
		
		int it0 = 32;
		int it1 = 0;
		int x = 0, y = 0;
		while(it0 < 1056){
			p->tiles[it1/32][it1%32] = buffer[it0];
			it0++;
			it1++;
		}
		
		delete [] buffer;
		return true;
	}else{
	    std::cout << "UNABLE TO OPEN FILE: " << filename << "\n";
	}
	
	return false;
}










bool exportPuzzle(puzzle* p, std::string filename){
	char* buffer = new char[1056];
	std::ofstream file(filename, std::ios::binary);
	
	if(file.is_open()){
		file.seekp(0, std::ios::beg);
		
		std::string headerStr = "SWTXBORD";
		for(int i = 0; i < 8; i++)
		    buffer[i] = headerStr[i];
		
		buffer[0x10] = p->time >> 8;
		buffer[0x11] = p->time & 0xFF;
		buffer[0x12] = getFloorStateID(p->state.r);
		buffer[0x13] = getFloorStateID(p->state.g);
		buffer[0x14] = getFloorStateID(p->state.b);
		buffer[0x15] = getFloorStateID(p->state.m);
		buffer[0x16] = getFloorStateID(p->state.y);
		buffer[0x17] = getFloorStateID(p->state.c);
		buffer[0x18] = p->ex % 32;
		buffer[0x19] = p->ey % 32;
		buffer[0x1A] = p->ox % 32;
		buffer[0x1B] = p->oy % 32;

        int it = 32;
        for(int i = 0; i < 32; i++){
            for(int j = 0; j < 32; j++){
                buffer[it] = p->tiles[i][j];
                it++;
            }
        }
		
		file.write(buffer,1056);
		file.close();
		delete [] buffer;
		return true;
	}
	
	return false;
}


















