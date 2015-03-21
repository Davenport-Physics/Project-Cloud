/*
 * controls.h
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


#ifndef CONTROLS_H
#define CONTROLS_H

#include <iostream>
#include <cstring>
#include <SDL2/SDL.h>

#include "engine.h"

#define NUMCONTROLS 5

using std::string;
using std::cout;

enum ControlType {
	
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	JOURNAL,
	ENTER,
	QUIT,
	NOTSET
	
};

//TODO save keys to the savefile
class Controls {
	
private:

	char controls[NUMCONTROLS];
	static const char ConstControls[2];
	
	string control_types[NUMCONTROLS];
	
	void initialize_control_types();

public:

	Controls();
	Controls(char *controls);
	~Controls();
	
	void set_controls_to_default();
	void set_controls_to_chars(char *controls);
	void set_controls_manually();
	
	void print_controls();
	
	enum ControlType check_control(char control);
	enum ControlType get_input(SDL_Event *event);
	
};

char get_raw_input(SDL_Event *event);

extern Controls UserControls;

#endif

