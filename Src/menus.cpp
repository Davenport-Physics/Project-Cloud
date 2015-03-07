//      MainMenu.cpp
//      
//      Copyright 2011-2015 Michael Davenport
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

static Pointer MenuPointer = {0, 0};

static const PointerVars MainMenuVars = {2, 2, 3, 5, 7, 9};
static const Pointer NewGamePointer   = {3, 5};
static const Pointer LoadGamePointer  = {5, 7};
static const Pointer OptionsPointer   = {7, 9};
static char MainMenuArray[10][22] = {
{' ','/','\\','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','/','\\',' '},
{'<','(',')','{','M','i','d','n','i','g','h','t',' ','C','l','o','u','d','}','(',')','>'},
{' ',' ','\\','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',' ',' ',' '},
{' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ','\\',' ',' ',' ','_','_','_','_','_','_','_','_',' ',' ',' ',' ',' ',' '},
{' ',' ',' ','>','}','\\','_','/','N','e','w',' ','G','a','m','e',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ','\\',' ',' ',' ','_','_','_','_','_','_','_','_','_',' ',' ',' '},
{' ',' ',' ',' ',' ',' ','}','\\','_','/','L','o','a','d',' ','G','a','m','e',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ','\\',' ',' ',' ','_','_','_','_','_','_','_',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ','}','\\','_','/','O','p','t','i','o','n','s',' ',' ',' '}};

static const PointerVars OptionsVars = {0, 2, 0, 0, 0, 2};
static const Pointer ControlsPointer = {0, 0};
static const Pointer CreditsPointer  = {0, 2};
static char OptionsArray[5][10] = 
{{'>','C','o','n','t','r','o','l','s',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ','C','r','e','d','i','t','s',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};


static const PointerVars ControlsVars     = {0, 2, 0, 0, 0, 2};
static const Pointer ViewControlsPointer  = {0, 0};
static const Pointer ChangeControlPointer = {0, 2}; 
static char ControlsMenuArray[3][20] = 
{{'>','V','i','e','w',' ','C','o','n','t','r','o','l','s',' ',' ',' ',' ',' ',' '},
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
 {' ',' ',' ',' ','(','/','d','e','v','/','z','e','r','o',')',' ',' ',' ',' ',' '},
 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};



void ResetPointers(enum MenuContext CurrentMenuContext) {
	
	
	switch (CurrentMenuContext) {
	
		case MAINMENU:
		
			MenuPointer.x = MainMenuVars.Min_x; 
			MenuPointer.y = MainMenuVars.Min_y;
			break;
			
		case OPTIONS:
		
			MenuPointer.x = OptionsVars.Min_x;
			MenuPointer.y = OptionsVars.Min_y;
			break;
			
		case CONTROLS:
		
			MenuPointer.x = ControlsVars.Min_x;
			MenuPointer.y = ControlsVars.Min_y;
			break;
			
		default: MenuPointer.x = MenuPointer.y = 0; break;
		
	}
	
}

/*
 * TODO, because the arrays are static, there needs to be a simple
 * way to remove extra pointers from the array.
 * 
 * */
void RemoveExtraPointers(enum MenuContext CurrentMenuContext) {

	PointerVars TempVars;
	try {
		
		TempVars = GetPointerVars(CurrentMenuContext);
		
	} catch (exception &e) {
	
		return;
		
	}
	
	int temp_x = TempVars.Min_x;
	int temp_y = TempVars.Min_y;
	
	while (temp_x <= TempVars.Max_x) {
	
		if (temp_x != MenuPointer.x && temp_y != MenuPointer.y) {
		
			switch (CurrentMenuContext) {
			
				case MAINMENU: MainMenuArray[temp_x][temp_y]     = ' '; break;
				case OPTIONS:  OptionsArray[temp_x][temp_y]      = ' '; break;
				case CONTROLS: ControlsMenuArray[temp_x][temp_y] = ' '; break;
				default: return; break;
				
			}
			
		}
		
		temp_x += TempVars.Dx;
		temp_y += TempVars.Dy;
		
	}
	
} 

enum MenuContext UpdatePointer(enum ControlType type, enum MenuContext CurrentMenuContext) {
	
	PointerVars Vars;
	try {
		
		Vars = GetPointerVars(CurrentMenuContext);
		
	} catch (exception &e) {
	
		return CurrentMenuContext;
		
	}
	
	switch (type) {
	
		case UP: 
		
			if (MenuPointer.y != Vars.Min_y && MenuPointer.x != Vars.Min_x) {
				
				MenuPointer.y -= Vars.Dy;
				MenuPointer.x -= Vars.Dx;
				
			}
			break;
			
		case DOWN:
		
			if (MenuPointer.y != Vars.Max_y && MenuPointer.x != Vars.Max_x) {
			
				MenuPointer.y += Vars.Dy;
				MenuPointer.x += Vars.Dx;
				
			}
			break;
			
		case ENTER:
		
			switch (CurrentMenuContext) {
			
				case MAINMENU: 
				
					if (MenuPointer.x == NewGamePointer.x && MenuPointer.y == NewGamePointer.y) {
						
						return NEWGAME;
						
					} else if (MenuPointer.x == LoadGamePointer.x && MenuPointer.y == LoadGamePointer.y) {
						
						return LOADGAME;
						
					} else if (MenuPointer.x == OptionsPointer.x && MenuPointer.y == OptionsPointer.y) {
					
						return OPTIONS;
						
					}
					break;
					
				case OPTIONS:
				
					if (MenuPointer.x == ControlsPointer.x && MenuPointer.y == ControlsPointer.y) {
					
						return CONTROLS;
						
					} else if (MenuPointer.x == CreditsPointer.x && MenuPointer.y == CreditsPointer.y) {
						
						return CREDITS;
						
					}
					break;
					
				case CONTROLS:
				
					if (MenuPointer.x == ViewControlsPointer.x && MenuPointer.y == ViewControlsPointer.y) {
					
						return VIEWCONTROLS;
						
					} else if (MenuPointer.x == ChangeControlPointer.x && MenuPointer.y == ChangeControlPointer.y) {
						
						return CHANGECONTROLS;
						
					}
					
				default: return CurrentMenuContext; break;
				
			}
		
			break;
			
		default: return CurrentMenuContext; break;
			
	}
	
	RemoveExtraPointers(CurrentMenuContext);
	
	return CurrentMenuContext;
	
}

enum MenuContext UpdateMenu(enum ControlType type, enum MenuContext CurrentMenuContext) {
	
	enum MenuContext TempMenuContext = UpdatePointer(type, CurrentMenuContext);
	
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
	
	return TempMenuContext;
	
}

PointerVars GetPointerVars(enum MenuContext CurrentMenuContext) {

	switch (CurrentMenuContext) {
		
		case MAINMENU: return MainMenuVars; break;
		case OPTIONS:  return OptionsVars; break;
		case CONTROLS: return ControlsVars; break;
		default: throw invalid_argument("No Structure to return"); break;
		
	}
	
}
