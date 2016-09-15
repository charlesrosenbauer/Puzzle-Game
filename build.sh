#!/bin/sh

g++ -lSDL -lSDL_mixer -o puzzle src/core/main.cpp src/core/mainloop.cpp src/core/render.cpp src/core/objects.cpp src/core/loader.cpp src/core/ui.cpp src/structs/sortstack.cpp
