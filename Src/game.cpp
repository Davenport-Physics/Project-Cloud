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
 * TODO
 * 
 * player x and y pointers are not passed to the map objects.
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

		if (get_map_type() == GENERATION) {
		
			for ( int x = 0; x < NUM_MAPS; x++ ) {
		
				if (get_map_type() == GENERATION) {
		
					MapGenerator temp(x);
					maps.push_back(temp.get_map_object_heap());
			
				}
		
			}
		
			player = new Player(name, "GeneratedMap0");
			maps[0]->SetPlayerPosition(&player->vars.x, &player->vars.y);
			player->vars.x = player->vars.y = 1;
			
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

	return NEWGAME;

}

/*
 * SaveGame
 * 
 * This function saves a variety of variables to a file specified by the
 * SaveFileName static string variable.
 * 
 * */
void SaveGame() {
	
	ofstream outfile(SaveFileName.c_str());
	
	player->SavePlayer(&outfile);
	
	for (unsigned int x = 0; x < maps.size();x++) {
	
		maps[x]->SaveMap(&outfile);
		
	}
	
	outfile.close();
	
}

/*
 * LoadGame
 * 
 * This function will eventually load variables from a file.
 * 
 * TODO This function is not complete.
 * 
 * */
enum GameContext LoadGame() {
	
	ifstream infile(SaveFileName.c_str());
	
	
	
	infile.close();
	
	return LOADGAME;
	
}

/*
 * UpdateGame
 * 
 * This function handles both player input, and also updating surfaces
 * that the game engine will eventually render.
 * 
 * */
enum GameContext UpdateGame(char Input) {

	if (UserControls.check_control(Input) == QUIT)
		return NOT_IN_GAME;
		
	HandleGameInput(Input);
	
	maps[0]->print_map_around_player(10);
	
	return INGAME;
}

void HandleGameInput(char Input) {
	
	switch (UserControls.check_control(Input)) {
	
		case UP:
		
			if (maps[0]->check_if_player_can_move(player->vars.x, player->vars.y-1) == YES)
				player->vars.y -= 1;
			break;
		case DOWN:
		
			if (maps[0]->check_if_player_can_move(player->vars.x, player->vars.y+1) == YES)
				player->vars.y += 1;
			break;
		case LEFT:
		
			if (maps[0]->check_if_player_can_move(player->vars.x-1, player->vars.y) == YES)
				player->vars.x -= 1;
			break;
		case RIGHT:
		
			if (maps[0]->check_if_player_can_move(player->vars.x+1, player->vars.y) == YES)
				player->vars.x += 1;
			break;
			
		default: break;
		
	}
	
}
