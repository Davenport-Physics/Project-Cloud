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

#include "map.h"
#include "share.h"
#include "engine.h"
#include "controls.h"
#include "character.h"


using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;

enum SuccessFailure {

	SUCCESS = 0,
	FAILURE
	
};

enum Saves {
	
	FIRST = 0,
	SECOND,
	THIRD,
	FILLED,
	EMPTY
	
};


string CheckForSaves(string filename);

void InitConfigFile();	
	
bool determine_window_height(string str);
bool determine_window_width(string str);
bool determine_rendering_type(string str);
bool determine_map_type(string str);
bool determine_max_fps(string str);
	
int get_window_height();
int get_window_width();
int get_max_fps();
	
enum TextRendering get_rendering_type();
enum MapType get_map_type();

#endif

