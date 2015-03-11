/*
 * game.h
 * 
 * Copyright 2015 Michael Davenport <Davenport.physics@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <fstream>

#include <SDL2/SDL.h>

#include "map.h"
#include "init.h"
#include "engine.h"
#include "controls.h"
#include "character.h"


enum GameContext {
	
	NEWGAME = 0,
	LOADGAME,
	INGAME,
	NOT_IN_GAME
	
};

void InitializeGameState(string SaveFile, SDL_Event *event);
void DeinitializeGameState();

void NewGame();
void LoadGame();
void SaveGame();

enum GameContext UpdateGame(enum GameContext context);

#endif

