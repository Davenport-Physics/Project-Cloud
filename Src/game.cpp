/*
 * game.cpp
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

#include "game.h"

using std::vector;
using std::ifstream;
using std::ofstream;

static string SaveFileName = "";
static Player *player      = NULL;
static vector<Map *> maps;

static SDL_Event *Event;

void InitializeGameState(string SaveFile, SDL_Event *event) {

	SaveFileName = SaveFile;
	Event        = event;
	
}
void DeinitializeGameState() {

	SaveFileName = "";
	
	for (unsigned int x = 0;x < maps.size(); x++) {
	
		delete maps[x];
		
	}
	maps.clear();
	
	delete player;
	
}

void NewGame() {
	
	string name = "";

	char c;
	clear_screen();
	draw_string("Please enter your name -> " + name);
	while ((c = get_raw_input(Event)) != '\n') {
		
		if (c == SDLK_BACKSPACE) {
		
			name = name.substr(0, name.length() - 1);
			
			
		} else {
			
			name += c;
		
		}
		clear_screen();
		draw_string("Please enter your name -> " + name);
		
	}
	
	/*
	 * TODO
	 * Add static support
	 * 
	 * */
	if (UserConfig.get_map_type() == GENERATION) {
		
		for ( int x = 0; x < NUM_MAPS; x++ ) {
		
			if (UserConfig.get_map_type() == GENERATION) {
		
				MapGenerator temp(x);
				maps[x] = temp.get_map_object_heap();
			
			}
		
		}
		
		player = new Player(name, "GeneratedMap0");
			
	} else if (UserConfig.get_map_type() == STATIC) {
		
		/*
		 * Add static map support. This will probably be
		 * implemented in lua later on.
		 * 
		 * */
		
	} else {
	
		DrawError_andQuit("Map type not specified for some reason");
		
	}

}

void SaveGame() {
	
	ofstream outfile(SaveFileName.c_str());
	
	player->SavePlayer(&outfile);
	
	for (unsigned int x = 0; x < maps.size();x++) {
	
		maps[x]->SaveMap(&outfile);
		
	}
	
	outfile.close();
	
}
void LoadGame() {
	
	ifstream infile(SaveFileName.c_str());
	
	
	
	infile.close();
	
	
}
