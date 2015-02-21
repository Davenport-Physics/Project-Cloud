/*
 * engine.cpp
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

#include "engine.h"

static const string FontPath = "Fonts/LiberationMonoRegular.ttf";

static SDL_Window *Window;
static SDL_Surface *Screen;

static TTF_Font *Font;

static Text RenderingType;

void init_engine(Text type) {
	
	SDL_Init(SDL_INIT_VIDEO);

	Window = SDL_CreateWindow("Midnight-Cloud",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
							800,
							800,
							SDL_WINDOW_SHOWN);
							
	Screen = SDL_GetWindowSurface(Window);
	
	if (!TTF_Init() == -1) {
	
		cout << "Error initializing True Text Font Engine";
		
	}
	
	/*
	 * Might want to give variable font depending on resolution
	 * 
	 * */
	Font = TTF_OpenFont(FontPath.c_str(), 20);
	
	/*
	 * Might give the user the possibility of changing rendering type
	 * at runtime, to give variable quality.
	 * 
	 * */
	RenderingType = type;
	
}

void quit_engine() {

	SDL_FreeSurface(Screen);
	SDL_DestroyWindow(Window);
	SDL_Quit();
	
}
