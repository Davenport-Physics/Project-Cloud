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

static const string FontPath = "Fonts/LiberationMono-Regular.ttf";

static SDL_Window *Window	= NULL;
static SDL_Surface *Screen	= NULL;
static TTF_Font *Font 		= NULL;

static SDL_Color Color 				= {255, 255, 255};
static SDL_Color BackgroundColor	= {0, 0, 0};

static Text RenderingType;

static SDL_Surface *(*RenderFunction)(TTF_Font *, const char *, SDL_Color);

void update_window();

void init_engine(Text type) {
	
	SDL_Init(SDL_INIT_VIDEO);

	Window = SDL_CreateWindow("Midnight-Cloud",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
							800,
							800,
							SDL_WINDOW_SHOWN);
							
	Screen = SDL_GetWindowSurface(Window);
	
	if (TTF_Init() == -1) {
	
		cout << "Error initializing True Text Font Engine: " << TTF_GetError();
		exit(2);
		
	}
	
	/*
	 * Might want to give variable font depending on resolution
	 * 
	 * */
	Font = TTF_OpenFont(FontPath.c_str(), 20);
	
	if (!Font) {
		
		cout << "Error opening font: " << TTF_GetError() << "\n";
		exit(2);
		
	}
	
	/*
	 * Might give the user the possibility of changing rendering type
	 * at runtime, to give variable quality.
	 * 
	 * */
	RenderingType = type;
	
	/*
	 * TODO, add shaded option.
	 * 
	 * */
	switch (RenderingType) {
	
		case FAST: 		RenderFunction = TTF_RenderText_Solid; break;
		case SHADED:
		case BLENDED:	RenderFunction = TTF_RenderText_Blended; break;
		
		
	}
	
}

void draw_2d_array(char **array, int rows) {
	
	SDL_FillRect(Screen, NULL, 0x000000);
	SDL_UpdateWindowSurface(Window);
	
	SDL_Surface *Surface;
	SDL_Rect Rect;
	
	Rect.x = 0;
	
	for (int y = 0;y < rows; y++) {
	
		Rect.y = y * 20;
		
		if (!(Surface = RenderFunction(Font, array[y], Color))) {
		
			cout << "Something went wrong with drawing 2D array";
			
			exit(2);
			
		} else {
		
			SDL_BlitSurface(Surface, NULL, Screen, &Rect);
			SDL_FreeSurface(Surface);
			
		}
		
	}
	
	SDL_UpdateWindowSurface(Window);
	
}

void quit_engine() {

	SDL_FreeSurface(Screen);
	SDL_DestroyWindow(Window);
	SDL_Quit();
	
}
