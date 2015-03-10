//      main.cpp
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


#include <iostream>
#include <vector>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <pthread.h>

#include "controls.h"
#include "init.h"
#include "menus.h"
#include "music.h"
#include "character.h"
#include "map.h"
#include "mygetch.h"
#include "engine.h"

bool UpdateState(enum ControlType type);
void UpdateState_Menu(enum ControlType type);

//static int SaveChoice;

#if __unix

static const string files[3] = {"Data/Saves/save1.db","Data/Saves/save2.db","Data/Saves/save3.db"};

#elif __WIN32

static const string files[3] = {"Data\\Saves\\save1.db", "Data\\Saves\\save2.db", "Data\\Saves\\save3.db"};

#endif
static vector<Map *> maps(30);
static Player *player = NULL;

static MenuContext CurrentMenuContext = MAINMENU;

/*
 * TODO init functions return struct player_vars, which is instantly
 * passed to an Player object.
 * 
 * TODO Set up music variables.
 * 
 * */
int main(int argc, char **argv) {
	
	srand(time(0));
	
	SDL_Event event;
	bool GameLoopDone = false;
	
	SDL_StartTextInput();
	init_sound_engine();
	init_engine(UserConfig.get_rendering_type(), UserConfig.get_window_height(), UserConfig.get_window_width());
	create_music_thread(TITLE);
	
	while (!GameLoopDone) {
		
		GameLoopDone = UpdateState(UserControls.get_input(&event));
		render();
		
		SDL_Delay(1000/60);
		
	}
	stop_music_thread();
	
	quit_engine();
	quit_sound_engine();
	
	delete player;
	
	return 0;
}

/*
 * TODO
 * 
 * There needs to be several types of quits. One quit that exits the game
 * fully. The other quit that just brings the player back to a previous
 * context.
 * 
 * */
bool UpdateState(enum ControlType type) {
	
	clear_screen();
	switch (CurrentRenderingContext) {
		
		case MENU: 
		
			UpdateState_Menu(type);
			break;
			
		default: break;
		
	}
	switch (type) {
		
		case QUIT: return true;  break;
		default:   return false; break;
		
	}
	
}

void UpdateState_Menu(enum ControlType type) {
	
	MenuContext (*MenuFunction)();
	switch (CurrentMenuContext) {
		
		case MAINMENU: MenuFunction = &UpdateMainMenu;    break;
		case OPTIONS:  MenuFunction = &UpdateOptionsMenu; break;
		case CREDITS:  MenuFunction = &RunCredits;        break;
		
		default: return; break;
		
	}
	
	CurrentMenuContext = UpdateMenu(type, MenuFunction, CurrentMenuContext);
	
}
