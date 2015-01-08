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


#include <pthread.h>

#include "controls.h"
#include "init.h"
#include "menus.h"
#include "music.h"
#include "character.h"
#include "generation.h"
#include "mygetch.h"

int pick_save(string *saves);
int handle_user_input(int input);
int get_user_input();

void run_game();

static string files[3] = {"Saves/save1.db","Saves/save2.db","Saves/save3.db"};
static int SaveChoice;

static vector<Map *> maps(30);
static Player *player = NULL;

/*
 * TODO init functions return struct player_vars, which is instantly
 * passed to an Player object.
 * 
 * TODO Set up music variables.
 * 
 * */
int main(int argc, char **argv) {
	
	srand(time(0));
	
	string saves[3];
	
	create_music_thread(TITLE);
	int game = main_menu();
	while (game != EXITGAME) {
		
		stop_music_thread();
		for (int x = 0; x < 3;x++) {
		
			saves[x] = check_for_saves_db(files[x]); 
			
		}
	
		switch (game) {
		
			case NEWGAME:
				
				if (pick_save(saves) != FILLED) {
				
					player = new_game(files[SaveChoice] , &maps);
				
				//TODO prompt the user to make sure they want to overwrite	
				} else {
					
					continue;
					
				}
				
				run_game();
			
			break;
			
			case LOADGAME:
				
				if (pick_save(saves) == FILLED) {
				
					player = load_game(files[SaveChoice], &maps);
				
				//TODO tell user there is no save file	
				} else {
				
					continue;
					
				}
				
				run_game();
			
			break;
			
			case OPTIONS:
			
				switch (options()) {
				
					case CONTROLS: controls(); break;
					case CREDITS: credits(); break;
					
				}
			
			break;
			
			
		}
		create_music_thread(TITLE);
		game = main_menu();
		
	}
	
	delete player;
	
	return 0;
}

int pick_save(string *saves) {
	
	SaveChoice = show_saves(saves);
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
	maps[player->vars.MapIndex]->transition_to_new_map(&player->vars.x,&player->vars.y,FORWARD);
	
	do {
		
		system("clear");
		
		maps[player->vars.MapIndex]->print_map_around_player(10);
		
	} while (get_user_input() != QUIT);
	
	stop_music_thread();
}

int get_user_input() {

		
		char command = mygetch();
		
		//TODO refactor using a function.
		switch (UserControls.check_control(command)) {
		
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
	
}

int handle_user_input(int input) {
	
	switch (input) {
		
		case NO: return NO;
		case SAVE: save_game_db(files[SaveChoice],player,maps); mygetch(); return NO; break;
		case GOLD: player->add_random_gold(); mygetch(); break;
	
	}
	return YES;
	
}
