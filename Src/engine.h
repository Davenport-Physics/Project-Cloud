/*
 * engine.h
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

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using std::string;
using std::cout;

enum TextRendering {
	
	FAST = 0,
	SHADED,
	BLENDED
	
};

enum RenderingContext {
	
	MENU = 0,
	BOTTOMTOP,
	GAME
	
};

void init_engine(enum TextRendering type, int Height, int Width);

/*
 * TODO add parameter to change parameter. This will effect how append,
 * works as well.
 * 
 * */
 
void draw_1d_array(char *array);
void draw_2d_array(char **array, int rows);
void draw_string(string str);

void draw_append_1d_array(char *array);
void draw_append_2d_array(char **array, int rows);
void draw_append_string(string str);
void draw_append_char_horizontal(char c);
void draw_append_string_horizontal(string str);

void draw_animation_bottom_top(char **array, int rows);

void render();
void quit_engine();
void clear_screen();
void reset_vertical();
void reset_horizontal();

template<int numrows, int numcolumns>
void draw_2d_stack_array(char (&array)[numrows][numcolumns], void (*DrawFunction)(char **, int)) {

	char **Stack = new char *[numrows];
	
	for (int y = 0;y < numrows;y++) {
	
		Stack[y] = new char[numcolumns + 1];
		
		strncpy(Stack[y], array[y], numcolumns);
		Stack[y][numcolumns] = '\0';
		
	}
	
	DrawFunction(Stack, numrows);
	
	delete [] Stack;
}

extern RenderingContext CurrentRenderingContext;

#endif

