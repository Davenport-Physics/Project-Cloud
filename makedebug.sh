#!/bin/bash

cd Src

clang++ -Wall -fsanitize=address -g -o mc *.cpp -lSDL2 -lSDL2_mixer -lSDL2_ttf -pthread

cd ..
cp Src/mc mc
gdb mc
