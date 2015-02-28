//      init.h
//      
//      Copyright 2011-2015 Michael Davenport
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      
//      
#ifndef INIT_H
#define INIT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>

#include "character.h"
#include "controls.h"
#include "generation.h"
#include "share.h"
#include "database.h"
#include "engine.h"

using std::string;
using std::vector;

typedef enum SuccessFailure {

	SUCCESS = 0,
	FAILURE
	
} SuccessEnum;

typedef enum Saves {
	
	FIRST = 0,
	SECOND,
	THIRD,
	FILLED,
	EMPTY
	
} SavesEnum;

Player * new_game(string filename, vector<Map *> *maps);
Player * load_game_db(string filename, vector<Map *> *maps);

string check_for_saves_db(string fileame);
string convert_player_vars_to_string(Player *player);
string convert_map_vars_to_string(unsigned int index, Map *map);

void save_game_db(string filename, Player *player , vector<Map *> maps);

SuccessEnum load_player_vars_db(character *player , vector<string> str);
SuccessEnum load_maps_db(vector<Map *> *maps , vector<string> str);

#endif

