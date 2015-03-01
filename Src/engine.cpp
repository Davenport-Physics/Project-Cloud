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

static int WindowHeight = 1024;
static int WindowWidth  = 768;
static int FontSize		= 25;

static const string FontPath = "Data/Fonts/LiberationMono-Regular.ttf";

static SDL_Window *Window	= NULL;
static SDL_Surface *Screen	= NULL;
static TTF_Font *Font 		= NULL;

static SDL_Color Color 				= {255, 255, 255};
//static SDL_Color BackgroundColor	= {0, 0, 0};

//static SDL_Rect LastPosition;
static SDL_Rect LastRect;

static Text RenderingType;

static SDL_Surface *(*RenderFunction)(TTF_Font *, const char *, SDL_Color);

void update_window();

void init_engine(Text type, int Height, int Width) {
	
	SDL_Init(SDL_INIT_VIDEO);
	
	WindowHeight = Height;
	WindowWidth  = Width;

	Window = SDL_CreateWindow("Midnight-Cloud",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
							WindowHeight,
							WindowWidth,
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
	Font = TTF_OpenFont(FontPath.c_str(), FontSize);
	
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

void clear_screen() {
	
	LastRect.y = 0;
	LastRect.x = 0;
	
	SDL_FillRect(Screen, NULL, 0x000000);
	
	
}

void draw_2d_array(char **array, int rows) {
	
	clear_screen();
	
	SDL_Surface *Surface;
	SDL_Rect Rect;
	
	Rect.x = 0;
	
	for (int y = 0;y < rows; y++) {
	
		Rect.y = y * FontSize;
		
		if (!(Surface = RenderFunction(Font, array[y], Color))) {
		
			cout << "Something went wrong with drawing 2D array";
			
			exit(2);
			
		} else {
		
			SDL_BlitSurface(Surface, NULL, Screen, &Rect);
			SDL_FreeSurface(Surface);
			
		}
		
	}
	LastRect = Rect;
	
	SDL_UpdateWindowSurface(Window);
	
}
void draw_string(string str) {
	
	clear_screen();

	char *array = new char[str.length() + 1];
	strcpy(array, str.c_str());
	array[str.length()] = '\0';
	
	SDL_Surface *Surface;
	
	SDL_Rect Rect;
	Rect.y = 0;
	Rect.x = 0;
	
	if (!(Surface = RenderFunction(Font, array, Color))) {
	
		cout << "could not draw string";
		exit(2);
		
	} else {
	
		SDL_BlitSurface(Surface, NULL, Screen, &Rect);
		SDL_FreeSurface(Surface);
		
		SDL_UpdateWindowSurface(Window);
		
		/*
		 * TODO
		 * 
		 * May want to have last position variables.
		 * 
		 * */
		LastRect = Rect;
		
	}
	
	delete [] array;
	
}

void draw_append_string(string str) {
	
	char *array = new char[str.length() + 1];
	strcpy(array, str.c_str());
	array[str.length()] = '\0';
	
	SDL_Surface *Surface;
	
	if (!(Surface = RenderFunction(Font, array, Color))) {
	
		cout << "Something went wrong drawing string";
		exit(2);
		
	} else {
		
		LastRect.y += FontSize;
	
		SDL_BlitSurface(Surface, NULL, Screen, &LastRect);
		SDL_FreeSurface(Surface);
	
		SDL_UpdateWindowSurface(Window);
	}
	
	delete [] array;
	
}

void draw_append_char_horizontal(char c) {

	char array[2];
	array[0] = c;
	array[1] = '\0';

	SDL_Surface *Surface;
	
	/*
	 * TODO Fix this
	 * 
	 * There doesn't seem to be a good way to handle this, given that
	 * each character on the screen takes up a different amount of
	 * horizontal space, and drawing just to the right of a string of
	 * text is very inconsistent.
	 * 
	 * */
	LastRect.x += 20;
	
	if (!(Surface = RenderFunction(Font, array, Color))) {
		
		cout << "Could not append char horizontal";
		exit(2);
		
	} else {
		
		SDL_BlitSurface(Surface, NULL, Screen, &LastRect);
		SDL_FreeSurface(Surface);
		
		SDL_UpdateWindowSurface(Window);
		
	}
	
}

void draw_append_string_horizontal(string str) {

	SDL_Surface *Surface;
	
	if (!(Surface = RenderFunction(Font, (char *)str.c_str(), Color))) {
		
		
	} else {
	
		SDL_BlitSurface(Surface, NULL, Screen, &LastRect);
		SDL_FreeSurface(Surface);
		
		SDL_UpdateWindowSurface(Window);
		
	}
	
}


void draw_animation_bottom_top(char **array, int rows) {

	SDL_Surface *Surface;
	SDL_Rect Rect[rows];
	
	SDL_FillRect(Screen, NULL, 0x000000);
	SDL_UpdateWindowSurface(Window);
	
	for (int y = 0;y < rows;y++) {
	
		Rect[y].x = (WindowWidth / 2 - 100);
		Rect[y].y = (WindowHeight - FontSize) + y * FontSize;
		
	}
	
	while (Rect[rows - 1].y != 0) {
		
		for (int y = 0;y < rows;y++) {
			
			if (Rect[y].y < (WindowHeight - FontSize) && Rect[y].y > 0) {
			
				if (!(Surface = RenderFunction(Font, array[y], Color))) {
				
					cout << "Unable to run draw_animation_bottom_top function";
					exit(2);
				
				} else {
			
					SDL_BlitSurface(Surface, NULL, Screen, &Rect[y]);
					SDL_FreeSurface(Surface);
				
				}
				
			}
			
		}
		SDL_UpdateWindowSurface(Window);
		
		for (int y = 0;y < rows;y++) {
			
			Rect[y].y -= 1;
			
		}
		SDL_Delay(1000/60);
		
		clear_screen();
		
	}
	
}

void reset_horizontal() {

	LastRect.x = 0;
	
}
void reset_vertical() {

	LastRect.y = 0;
	
}

void quit_engine() {

	SDL_FreeSurface(Screen);
	SDL_DestroyWindow(Window);
	SDL_Quit();
	
}
