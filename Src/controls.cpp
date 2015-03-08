/*
 * controls.cpp
 * 
 * Copyright 2014-2015 Michael Davenport <Davenport.physics@gmail.com>
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

#include "controls.h"

Controls UserControls;

Controls::Controls() {
	
	initialize_control_types();
	set_controls_to_default();
	
}

Controls::Controls(char *controls) {

	initialize_control_types();
	strcpy(this->controls , controls);
	
}

Controls::~Controls() {
	
	
}

void Controls::initialize_control_types() {
	
	this->control_types[0] = "Up";
	this->control_types[1] = "Down";
	this->control_types[2] = "Left";
	this->control_types[3] = "Right";
	this->control_types[4] = "Quit";
	this->control_types[5] = "Journal";
	this->control_types[6] = "Enter";
	
}

void Controls::set_controls_to_default() {

	strcpy(this->controls , "wsadqj\n");
	
}

void Controls::set_controls_to_chars(char *controls) {

	strcpy(this->controls , controls);
	
}

void Controls::set_controls_manually() {
	
	bool Error;
	
	do {
	
		Error = false;
		clear_screen();
		for (int i = 0; i < this->length;i++) {
	
			draw_append_string(this->control_types[i]);
			this->controls[i] = get_raw_input();
			
			draw_append_char_horizontal(this->controls[i]);
			reset_horizontal();
		
		}
		
		for (int x = 0;x < this->length;x++)
		for (int i = x+1;i < this->length;i++) {
		
			if (this->controls[x] == this->controls[i]) {
			
				Error = true;
				
			}
			
		}	
		
	} while (Error == true);
	
}

void Controls::print_controls() {

	for (int i = 0; i < this->length; i++) {
	
		cout << this->controls[i] << "\n";
		
	}
	
}

enum ControlType Controls::check_control(char control) {

	for (int i = 0;i < this->length;i++) {
	
		if ( this->controls[i] == control ) {
		
			return (enum ControlType)i;
		
		}
		
	}
	
	return NOTSET;
	
}

/*
 * These functions will eventually use sdl, but for now they're still
 * using the terminal input.
 * 
 * */
enum ControlType Controls::get_input(SDL_Event *event) {
	
	if (SDL_PollEvent(event)) {
	
		switch (event->type) {
		
			case SDL_QUIT: 
			
				return QUIT; 
				break;
				
			case SDL_KEYDOWN:
				
				return ControlType(event->key.keysym.sym);
				break;
			
			default: 
			
				return NOTSET;
				break;
			
		}
		
	}
	
	return NOTSET;
	
}

char get_raw_input() {

	return mygetch();
	
}
