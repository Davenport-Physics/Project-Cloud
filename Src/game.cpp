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

#if __unix

static const string SaveFiles[3] = {
	"Data/Saves/save1",
	"Data/Saves/save2",
	"Data/Saves/save3"};

#elif __WIN32

static const string SaveFiles[3] = {
	"Data\\Saves\\save1", 
	"Data\\Saves\\save2", 
	"Data\\Saves\\save3"};

#endif

/*
 * InitializeGameState : SDL_Event
 * 
 * This function initializes variables that are required to have
 * a working game state.
 * 
 * */
void InitializeGameState(SDL_Event *event) {
	
	Event = event;
	
}
/*
 * DeinitializeGameState
 * 
 * This function resets the static variables to their initial state. 
 * 
 * */
void DeinitializeGameState() {

	SaveFileName = "";
	
	for (unsigned int x = 0;x < maps.size(); x++) {
	
		delete maps[x];
		
	}
	maps.clear();
	
	delete player;
	
}

/*
 * NewGame
 * 
 * This function initializes a variety of static variables that will be used
 * once the game is actually running. For example it initializes the name
 * of the player and also the maps that the player is going play on.
 * 
 * */
enum GameContext NewGame(char Input) {

	static string name = "";
	
	draw_string("Please enter your name -> " + name);
	if (Input != '\n') {
		
			if (Input == '\0') {
				
				return NEWGAME;
				
			} else if (Input == SDLK_BACKSPACE) {
		
				name = name.substr(0, name.length() - 1);
			
			
			} else {
			
				name += Input;
		
			}
		
	} else {
		goto skip;
		if (get_map_type() == GENERATION) {
		
			for ( int x = 0; x < NUM_MAPS; x++ ) {
		
				if (get_map_type() == GENERATION) {
		
					MapGenerator temp(x);
					maps[x] = temp.get_map_object_heap();
			
				}
		
			}
		
			player = new Player(name, "GeneratedMap0");
			
		} else if (get_map_type() == STATIC) {
		
			/*
			* Add static map support. This will probably be
			* implemented in lua later on.
			* 
			* */
		
		} else {
	
			DrawError_andQuit("Map type not specified for some reason");
		
		}
		
		return INGAME;
		
	}
	skip:
	return NEWGAME;

}

void SaveGame() {
	
	ofstream outfile(SaveFileName.c_str());
	
	player->SavePlayer(&outfile);
	
	for (unsigned int x = 0; x < maps.size();x++) {
	
		maps[x]->SaveMap(&outfile);
		
	}
	
	outfile.close();
	
}
enum GameContext LoadGame() {
	
	ifstream infile(SaveFileName.c_str());
	
	
	
	infile.close();
	
	return LOADGAME;
	
}

enum GameContext UpdateGame(enum GameContext context) {

	
	return NOT_IN_GAME;
	
}
