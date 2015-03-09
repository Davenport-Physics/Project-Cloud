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

int pick_save(string *saves);
int determine_new_game(string *saves);
int determine_load_game(string *saves);
int handle_user_input(int input);
int get_user_input();


void run_game();
bool UpdateState(enum ControlType type);

//static int SaveChoice;
static string files[3] = {"Data/Saves/save1.db","Data/Saves/save2.db","Data/Saves/save3.db"};
static vector<Map *> maps(30);
static Player *player = NULL;

static enum MenuContext CurrentMenuContext = MAINMENU;

/*
 * TODO init functions return struct player_vars, which is instantly
 * passed to an Player object.
 * 
 * TODO Set up music variables.
 * 
 * */
int main(int argc, char **argv) {
	
	srand(time(0));
	
	init_sound_engine();
	create_music_thread(TITLE);
	
	bool GameLoopDone = false;
	
	init_engine(UserConfig.get_rendering_type(), UserConfig.get_window_height(), UserConfig.get_window_width());
	SDL_StartTextInput();
	SDL_Event event;
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
		
		case MENU: UpdateMenu(type, CurrentMenuContext); break;
		default: break;
		
	}
	switch (type) {
		
		case QUIT: return true;  break;
		default:   return false; break;
		
	}
	
}


/*int determine_new_game(string *saves) {

	int choice = pick_save(saves);
				
	if (choice == QUIT) {
		
		return QUIT;
				
	} else if (choice != FILLED) {
					
		return YES;
					
	} else {
				
		draw_append_string("Do you wish to overwrite this file? y/n");
		
		if(get_raw_input() == 'y' || get_raw_input() == 'Y') {
		
			return YES;
			
		} else {
		
			return NO;
			
		}
									
	}
	
}

int determine_load_game(string *saves) {
	
	int choice = pick_save(saves);
	if (choice == FILLED) {
				
		return YES;
				
	} else if (choice == QUIT) {
	
		return QUIT;
	
	} else {
				
		draw_append_string("There is no save file here");
		get_raw_input();
		return NO;
					
	}
	
}


int pick_save(string *saves) {
	
	SaveChoice = show_saves(saves);
	
	if (SaveChoice == -1) { 
	
		return QUIT;
		
	}
	
	if (saves[SaveChoice].compare("empty") == 0) {
	
		return SaveChoice;
		
	} else {
		
		return FILLED;
		
	}
	
}

//TODO finish run_game
void run_game() {
	
	stop_music_thread();
	create_music_thread(RANDOM);
	
	//Index needs to be saved to file and loaded
	//maps[player->vars.MapIndex]->transition_to_new_map(&player->vars.x,&player->vars.y, FORWARD);
	
	do {
		
		maps[player->vars.MapIndex]->print_map_around_player(10);
		
		string temp = "Health:" + SSTR(player->vars.PlayerHealth) + " Mana:" + convert_float_to_string(player->vars.Mana);
		temp 	   += " gold:" + SSTR(player->vars.gold);
		
		draw_append_string(temp);
		
	} while (get_user_input() != QUIT);
	
	stop_music_thread();
}

int get_user_input() {

		
		//TODO refactor using a function.
		switch (UserControls.get_input()) {
		
			case UP:
			
				if (handle_user_input(maps[player->vars.MapIndex]->check_if_player_can_move(player->vars.x,player->vars.y - 1)) == YES)
					player->vars.y -= 1;
			
			break;
			case DOWN:
			
				if (handle_user_input(maps[player->vars.MapIndex]->check_if_player_can_move(player->vars.x,player->vars.y + 1)) == YES)
					player->vars.y += 1;

				
			break;
			case LEFT:
			
				if (handle_user_input(maps[player->vars.MapIndex]->check_if_player_can_move(player->vars.x-1,player->vars.y)) == YES)				
					player->vars.x -= 1;

			break;
			case RIGHT:
			
				if (handle_user_input(maps[player->vars.MapIndex]->check_if_player_can_move(player->vars.x+1,player->vars.y)) == YES)
					player->vars.x += 1;
			
			break;
			case QUIT: return QUIT; break;
			default: cout << "command not implemented" << endl; break;
			
		}
	
	return 0;
	
}*/

/*
 * Transitioning does not use the new method yet. The lines are just
 * commented out
 * 
 * */
 
 /*
int handle_user_input(int input) {
	
	switch (input) {
		
		case NO: return NO; break;
		case SAVE: save_game_db(files[SaveChoice],player,maps); mygetch(); return NO; break;
		case GOLD: player->add_random_gold(); mygetch(); break;
		case FORWARD: 
		
			player->vars.MapIndex++; player->reset_positions();
			//maps[player->vars.MapIndex]->transition_to_new_map(&player->vars.x,&player->vars.y,FORWARD);
			
		break;
		case BACKWARD: 
		
			player->vars.MapIndex--; player->reset_positions(); 
			//maps[player->vars.MapIndex]->transition_to_new_map(&player->vars.x,&player->vars.y,BACKWARD);
		
		break;
	
	}
	return YES;
	
}*/
