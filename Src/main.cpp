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

void InitializeSystems();

bool UpdateState(char Input);
void UpdateState_Menu(char Input);
void UpdateState_Game(char Input);

void ResetState_Menu();
void ResetState_Game();
void ResetState_Rendering();

void ResetStates();

static MenuContext CurrentMenuContext           = MAINMENU;
static RenderingContext CurrentRenderingContext = MENU;
static GameContext CurrentGameContext           = NOT_IN_GAME;

static int MaximumFPS;

static SDL_Event event;

/*
 * TODO init functions return struct player_vars, which is instantly
 * passed to an Player object.
 * 
 * TODO Set up music variables.
 * 
 * */
int main(int argc, char **argv) {
	
	InitializeSystems();

	bool GameLoopDone = false;
	while (!GameLoopDone) {
		
		GameLoopDone = UpdateState(get_raw_input(&event));
		render();
		
		SDL_Delay(1000/MaximumFPS);
		
	}
	stop_music_thread();
	
	quit_engine();
	quit_sound_engine();
	
	return 0;
}

/*
 * InitializeSystems
 * 
 * Initializes the state of the program by calling a variety of 
 * initialize functions throughout the program.
 * 
 * */
void InitializeSystems() {
	
	srand(time(0));

	SDL_StartTextInput();
	InitConfigFile();
	init_sound_engine();
	init_engine(get_rendering_type(), get_window_height(), get_window_width());
	InitializeGameState(&event);
	MaximumFPS = get_max_fps();
	
	create_music_thread(TITLETRACK);
	
}


/*
 * 
 * UpdateState : enum ControlType
 * 
 * This function calls the correct update function depending on the
 * CurrentRenderingContext value. It returns a boolean function, that is
 * only false when the enum ControlType value is QUIT.
 * 
 * 
 * */
bool UpdateState(char Input) {
	
	clear_screen();
	switch (CurrentRenderingContext) {
		
		case MENU: 
		
			UpdateState_Menu(Input);
			break;
			
		case GAME:
		
			UpdateState_Game(Input);
			break;
			
		default: break;
		
	}
	switch (UserControls.check_control(Input)) {
		
		case QUIT: return true;  break;
		default:   return false; break;
		
	}
	
}

/*
 * UpdateState_Menu : enum ControlType
 * 
 * This function determines what Menu Function to call based
 * on the value stored in the variable CurrentMenuContext. It may
 * set up more specific conditions if a menu item has requirements that
 * are not needed by other menu functions.
 * 
 * */
void UpdateState_Menu(char Input) {
	
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
				
			CurrentMenuContext = UpdateMenu(UserControls.check_control(Input), MenuFunction, CurrentMenuContext);
			break;
	
	}
	
}

/*
 * UpdateState_Game : enum ControlType
 * 
 * This function determines which Game Function to called based
 * on the value stored in the variable CurrentMenuContext. If function
 * notices that the CurrentMenuContext does not correspond to any
 * game function, it will halt the program passing the value EXIT_FAILURE.
 * 
 * */

void UpdateState_Game(char Input) {

	if (CurrentGameContext == NOT_IN_GAME) {
		
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
		
	}
	
	switch (CurrentGameContext) {
	
		case NEWGAME:  CurrentGameContext = NewGame(Input);    break;
		case LOADGAME: CurrentGameContext = LoadGame();   break;
		case INGAME:   CurrentGameContext = UpdateGame(Input); break;
		
		default: 
			
			ResetStates();
			break;
			
	}
	if (CurrentGameContext == NOT_IN_GAME)
		ResetStates();
	
}

/*
 * ResetState_Menu
 * 
 * Resets the variable CurrentMenuContext to the default value being
 * MAINMENU
 * 
 * 
 * */

void ResetState_Menu() {

	CurrentMenuContext = MAINMENU;
	
}

/*
 * ResetState_Game
 * 
 * Resets the variable CurrentGameContext to the default value being
 * NOT_IN_GAME
 * 
 * */
void ResetState_Game() {

	CurrentGameContext = NOT_IN_GAME;
	
}

/*
 * ResetState_Rendering
 * 
 * Resets the variable CurrentRenderingContext to the default value
 * being MENU
 * 
 * */

void ResetState_Rendering() {

	CurrentRenderingContext = MENU;
	
}

/*
 * ResetStates
 * 
 * Resets the variables CurrentMenuContext, CurrentGameContext and
 * CurrentRenderingContext to their default values.
 * 
 * */

void ResetStates() {

	CurrentMenuContext      = MAINMENU;
	CurrentGameContext      = NOT_IN_GAME;
	CurrentRenderingContext = MENU;
	
}
