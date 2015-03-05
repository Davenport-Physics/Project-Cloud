//      MainMenu.cpp
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



#include "menus.h"

typedef struct PointerVars {
	
	int Dx, Dy;
	int Min_x, Min_y;
	int Max_x, Max_y;
	
}PointerVars;

typedef struct Pointer {
	
	int x, y;
	
}Pointer;

static Pointer MenuPointer = {0, 0};

static const PointerVars MainMenuVars = {2, 2, 3, 5, 7, 9};
static char MainMenuArray[10][22] = {
{' ','/','\\','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','/','\\',' '},
{'<','(',')','{','M','i','d','n','i','g','h','t',' ','C','l','o','u','d','}','(',')','>'},
{' ',' ','\\','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',' ',' ',' '},
{' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ','\\',' ',' ',' ','_','_','_','_','_','_','_','_',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ','}','\\','_','/','N','e','w',' ','G','a','m','e',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ','\\',' ',' ',' ','_','_','_','_','_','_','_','_','_',' ',' ',' '},
{' ',' ',' ',' ',' ',' ','}','\\','_','/','L','o','a','d',' ','G','a','m','e',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ','\\',' ',' ',' ','_','_','_','_','_','_','_',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ','}','\\','_','/','O','p','t','i','o','n','s',' ',' ',' '}};

static const PointerVars OptionsVars = {0, 2, 0, 0, 0, 2};
static char OptionsArray[5][10] = 
{{' ','C','o','n','t','r','o','l','s',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ','C','r','e','d','i','t','s',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};


static const PointerVars ControlsVars = {0, 2, 0, 0, 0, 2};
static char ControlsMenuArray[3][20] = 
{{' ','V','i','e','w',' ','C','o','n','t','r','o','l','s',' ',' ',' ',' ',' ',' '},
 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
 {' ','C','h','a','n','g','e',' ','C','o','n','t','r','o','l','s',' ',' ',' ',' '}};


static char CreditsArray[13][20] =
{{'C','r','e','d','i','t','s',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
 {'L','e','a','d',' ','P','r','o','g','r','a','m','m','e','r',' ',' ',' ',' ',' '},
 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
 {' ',' ',' ','M','i','c','h','a','e','l',' ','D','a','v','e','n','p','o','r','t'},
 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
 {'M','u','s','i','c',' ','b','y',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
 {' ',' ',' ','G','e','o','r','g','e',' ','M','i','t','c','h','e','l','l',' ',' '},
 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
 {' ',' ',' ',' ',' ',' ',' ','a','k','a',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
 {' ',' ',' ',' ','/','d','e','v','/','z','e','r','o',' ',' ',' ',' ',' ',' ',' '}};


void ResetPointers(enum MenuContext CurrentMenuContext) {
	
	
	switch (CurrentMenuContext) {
	
		case MAINMENU:
		
			pointer.x = MainMenuVars.Min_x; 
			pointer.y = MainMenuVars.Min.y;
			break;
			
		case OPTIONS:
		
			pointer.x = OptionsVars.Min_x;
			pointer.y = OptionsVars.Min_y;
			break;
			
		case CONTROLS:
		
			pointer.x = ControlsVars.Min_x;
			pointer.y = ControlsVars.Min_y;
			break;
			
		default: pointer.x = pointer.y = 0; break;
		
	}
	
} 

void UpdatePointer(enum ControlType type, enum MenuContext CurrentMenuContext) {
	
	PointerVars Vars;
	switch (CurrentMenuContext) {
		
		case MAINMENU: Vars = MainMenuVars; break;
		case OPTIONS:  Vars = OptionsVars; break;
		case CONTROLS: Vars = ControlsVars; break;
		default: return; break;
		
	}
	
	switch (type) {
	
		case UP: 
		
			if ()
		
		break;
		
	}
	
}

void UpdateMenu(enum MenuContext CurrentMenuContext) {
	
	void (*DrawFunction)(char **, int);
	switch (CurrentMenuContext) {
		
		case CREDITS: DrawFunction = &draw_animation_bottom_top; break;
		default:      DrawFunction = &draw_2d_array; break;
		
	}
	
	switch (CurrentMenuContext) {
	
		case MAINMENU: draw_2d_stack_array(MainMenuArray, DrawFunction); break;
		case OPTIONS:  draw_2d_stack_array(OptionsArray, DrawFunction); break;
		case CONTROLS: draw_2d_stack_array(ControlsMenuArray, DrawFunction); break;
		case CREDITS:  draw_2d_stack_array(CreditsArray, DrawFunction); break;
		default: break;
		
		
	}
	
}
