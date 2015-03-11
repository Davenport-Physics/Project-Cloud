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
#include <ctime>

#include <SDL2/SDL.h>
#include <pthread.h>

#include "map.h"
#include "game.h"
#include "init.h"
#include "menus.h"
#include "music.h"
#include "engine.h"
#include "controls.h"
#include "character.h"

bool UpdateState(enum ControlType type);
void UpdateState_Menu(enum ControlType type);
void UpdateState_Game(enum ControlType type);

void ResetState_Menu();
void ResetState_Game();
void ResetState_Rendering();

void ResetStates();

//static int SaveChoice;

#if __unix

static const string files[3] = {"Data/Saves/save1.db","Data/Saves/save2.db","Data/Saves/save3.db"};

#elif __WIN32

static const string files[3] = {"Data\\Saves\\save1.db", "Data\\Saves\\save2.db", "Data\\Saves\\save3.db"};

#endif

static MenuContext CurrentMenuContext           = MAINMENU;
static RenderingContext CurrentRenderingContext = MENU;
static GameContext CurrentGameContext           = NOT_IN_GAME;

static int MaximumFPS;

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
	create_music_thread(TITLETRACK);
	
	MaximumFPS = UserConfig.get_max_fps();
	cout << "MaxFPS = " << MaximumFPS;
	while (!GameLoopDone) {
		
		GameLoopDone = UpdateState(UserControls.get_input(&event));
		render();
		
		SDL_Delay(1000/MaximumFPS);
		
	}
	stop_music_thread();
	
	quit_engine();
	quit_sound_engine();
	
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
			
		case GAME:
		
			UpdateState_Game(type);
			break;
			
		default: break;
		
	}
	switch (type) {
		
		case QUIT: return true;  break;
		default:   return false; break;
		
	}
	
}

void UpdateState_Menu(enum ControlType type) {
	
	MenuContext (*MenuFunction)() = NULL;
	switch (CurrentMenuContext) {
		
		case MAINMENU: MenuFunction = &UpdateMainMenu;    break;
		case OPTIONS:  MenuFunction = &UpdateOptionsMenu; break;
		case CONTROLS: MenuFunction = &UpdateControlsMenu; break;
		
		default: break;
		
	}
		
	switch (CurrentMenuContext) {
		
		case MENU_NEWGAME:
		case MENU_LOADGAME:
		
			CurrentRenderingContext = GAME;
			break;
		
		/*
		 * Credits takes hold of the rendering context. The player cannot
		 * give input while it's running. 
		 * */
		case CREDITS: 
		
			if (GetCurrentTrack() != CREDITSTRACK) {
				
				stop_music_thread();
				create_music_thread(CREDITSTRACK);
				
			}
			
			CurrentMenuContext = RunCredits();
			
			if (CurrentMenuContext == MAINMENU) {
				
				stop_music_thread();
				create_music_thread(TITLETRACK);
				
			}
			break;
		
		default:
		
			if (MenuFunction == NULL)
				return;
				
			CurrentMenuContext = UpdateMenu(type, MenuFunction, CurrentMenuContext);
			break;
	
	}
	
}

void UpdateState_Game(enum ControlType type) {

	switch (CurrentMenuContext) {
	
		case MENU_NEWGAME:  CurrentGameContext = NEWGAME;  break;
		case MENU_LOADGAME: CurrentGameContext = LOADGAME; break;
		
		/*
		 * If the default is chosen, it means the game didn't change
		 * the MenuContext correctly, and this may go into an infinite
		 * loop. Best to just exit the game.
		 * 
		 * */
		default:
		
			cout << "Something seems to be wrong. UpdateState_Game. default called";
			exit(EXIT_FAILURE);
			break;
		
	}
	CurrentMenuContext = MAINMENU;
	
}

void ResetState_Menu() {

	CurrentMenuContext = MAINMENU;
	
}

void ResetState_Game() {

	CurrentGameContext = NOT_IN_GAME;
	
}

void ResetState_Rendering() {

	CurrentRenderingContext = MENU;
	
}

void ResetStates() {

	CurrentMenuContext      = MAINMENU;
	CurrentGameContext      = NOT_IN_GAME;
	CurrentRenderingContext = MENU;
	
}
