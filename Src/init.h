//      player.h
//      
//      Copyright 2011 Michael Davenport
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
#include "generation.h"
#include "share.h"
#include "database.h"

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using std::string;
using std::vector;

enum {
	
	FIRST = 0,
	SECOND,
	THIRD,
	FILLED,
	EMPTY
	
};

//new prototypes
Player * new_game(string filename, vector<Map *> *maps);
void save_game(string filename , Player *player , vector<Map *> maps);

string check_for_saves(string filename);

Player * load_game(string filename, vector<Map *> *maps);

void load_player_vars( character *player , ifstream *file);
void load_maps(character *player , ifstream *file , vector<Map *> *maps);

//database prototypes
string check_for_saves_db(string fileame);
string convert_player_vars_to_string(Player *player);
string convert_map_vars_to_string(unsigned int index, Map *map);

#endif

