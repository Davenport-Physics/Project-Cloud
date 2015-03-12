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

static Pointer MenuPointer = {3, 5};

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
{' ',' ',' ',' ','}','\\','_','/','N','e','w',' ','G','a','m','e',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ','\\',' ',' ',' ','_','_','_','_','_','_','_','_','_',' ',' ',' '},
{' ',' ',' ',' ',' ',' ','}','\\','_','/','L','o','a','d',' ','G','a','m','e',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ','\\',' ',' ',' ','_','_','_','_','_','_','_',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ','}','\\','_','/','O','p','t','i','o','n','s',' ',' ',' '}};

static const PointerVars OptionsVars = {0, 2, 0, 0, 0, 2};
static const Pointer ControlsPointer = {0, 0};
static const Pointer CreditsPointer  = {0, 2};
static char OptionsArray[5][10] = {
{' ','C','o','n','t','r','o','l','s',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ','C','r','e','d','i','t','s',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};


static const PointerVars ControlsVars     = {0, 2, 0, 0, 0, 2};
static const Pointer ViewControlsPointer  = {0, 0};
static const Pointer ChangeControlPointer = {0, 2}; 
static char ControlsMenuArray[3][20] = {
{' ','V','i','e','w',' ','C','o','n','t','r','o','l','s',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ','C','h','a','n','g','e',' ','C','o','n','t','r','o','l','s',' ',' ',' ',' '}};


static char CreditsArray[13][20] = {
{'C','r','e','d','i','t','s',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
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


MenuContext UpdateMenu(enum ControlType type, MenuContext (*MenuFunction)(), MenuContext CurrentMenuContext) {

	MenuContext TempMenuContext = CurrentMenuContext;
	switch (type) {
	
		case ENTER: 
		
			TempMenuContext = MenuFunction();
			
			if (TempMenuContext != CurrentMenuContext) {
				
				ResetPointers(CurrentMenuContext);
				RemoveExtraPointers(CurrentMenuContext);
				ResetPointers(TempMenuContext);
				
			}
			break;
			
		case NOTSET:
		
			SetMenuPointer(CurrentMenuContext);
			break;
			
		default:
		
			HandleBasicInputMenu(type, TempMenuContext);
			break;
		
	}
	
	switch (TempMenuContext) {
	
		case MAINMENU: draw_2d_stack_array(MainMenuArray, &draw_2d_array); break;
		case OPTIONS:  draw_2d_stack_array(OptionsArray,  &draw_2d_array); break;
		
		case CREDITS: break;
		/*
		 * The menu context isn't support yet, so it defaults to the
		 * previous context.
		 * 
		 * */
		default:
		
			cout << "MenuContext " << TempMenuContext << " is not supported\n";
			TempMenuContext = CurrentMenuContext;
			ResetPointers(TempMenuContext);
			RemoveExtraPointers(TempMenuContext);
			break;
		
	}
	
	return TempMenuContext;
	
}

/*
 * Update<context> handles the enter input. 
 * 
 * */
MenuContext UpdateMainMenu() {
	
	if (CheckPointerEquality(MenuPointer, NewGamePointer)) 
		return MENU_NEWGAME;
	else if (CheckPointerEquality(MenuPointer, LoadGamePointer))
		return MENU_LOADGAME;
	else if (CheckPointerEquality(MenuPointer, OptionsPointer))
		return OPTIONS;
	else
		return MAINMENU;
}

MenuContext UpdateOptionsMenu() {
	
	if (CheckPointerEquality(MenuPointer, ControlsPointer))
		return CONTROLS;
	else if (CheckPointerEquality(MenuPointer, CreditsPointer))
		return CREDITS;
	else
		return OPTIONS;
	
}

MenuContext UpdateControlsMenu() {

	if (CheckPointerEquality(MenuPointer, ViewControlsPointer))
		return VIEWCONTROLS;
	else if (CheckPointerEquality(MenuPointer, ChangeControlPointer))
		return CHANGECONTROLS;
	else
		return CONTROLS;
	
}

MenuContext RunCredits() {
	
	static AnimationBottomTop CreditsAnimation(ConvertStackArrayToHeap(CreditsArray), 13);
	
	if (CreditsAnimation.AnimationFinished() == true) {
	
		ResetPointers(MAINMENU);
		CreditsAnimation.ResetRects();
		return MAINMENU;
		
	} else {
	
		CreditsAnimation.UpdateFrame();
		return CREDITS;
		
	}
	
}

bool CheckPointerEquality(Pointer First, Pointer Second) {

	if (First.x == Second.x && First.y == Second.y) {
	
		return true;
		
	}
	
	return false;
	
}

void HandleBasicInputMenu(enum ControlType type, MenuContext CurrentMenuContext) {
	
	PointerVars Tempvars;
	
	try {
		
		Tempvars = GetCurrentPointerVars(CurrentMenuContext);
		
	} catch (exception &e) { return; }
	
	switch (type) {
	
		case UP:
			
			cout << "UP\n";
			if (MenuPointer.x >= Tempvars.Min_x && MenuPointer.y > Tempvars.Min_y ) {
				
				MenuPointer.x -= Tempvars.Dx;
				MenuPointer.y -= Tempvars.Dy;
				
			}
			break;
			
		case DOWN:
		
			cout << "DOWN\n";
			if (MenuPointer.x <= Tempvars.Max_x && MenuPointer.y < Tempvars.Max_y) {
				
				MenuPointer.x += Tempvars.Dx;
				MenuPointer.y += Tempvars.Dy;
				
			}
			break;
			
		default: break;
		
	}
	
	RemoveExtraPointers(CurrentMenuContext);
	SetMenuPointer(CurrentMenuContext);
	
}

void SetMenuPointer(MenuContext CurrentMenuContext) {
	
	switch (CurrentMenuContext) {
	
		case MAINMENU: 
		
			MainMenuArray[MenuPointer.y][MenuPointer.x] = '>'; 
			break;
			
		case OPTIONS:
		
			OptionsArray[MenuPointer.y][MenuPointer.x] = '>';
			break;
			
		default: break;
		
	}
	
}
 
void RemoveExtraPointers(MenuContext CurrentMenuContext) {

	PointerVars TempVars;
	try {
		
		TempVars = GetCurrentPointerVars(CurrentMenuContext);
		
	} catch (exception &e) {
	
		return;
		
	}
	
	int temp_x = TempVars.Min_x;
	int temp_y = TempVars.Min_y;
	
	
	while (temp_x <= TempVars.Max_x && temp_y <= TempVars.Max_y) {
	
		if (temp_x == MenuPointer.x && temp_y == MenuPointer.y) {
		
			
		} else {
			
			switch (CurrentMenuContext) {
			
				case MAINMENU: MainMenuArray[temp_y][temp_x]     = ' '; break;
				case OPTIONS:  OptionsArray[temp_y][temp_x]      = ' '; break;
				case CONTROLS: ControlsMenuArray[temp_y][temp_x] = ' '; break;
				default: return; break;
				
			}
			
		}
		
		temp_x += TempVars.Dx;
		temp_y += TempVars.Dy;
		
	}
	
} 

PointerVars GetCurrentPointerVars(MenuContext CurrentMenuContext) {

	switch (CurrentMenuContext) {
		
		case MAINMENU: return MainMenuVars; break;
		case OPTIONS:  return OptionsVars; break;
		case CONTROLS: return ControlsVars; break;
		default: throw invalid_argument("No Structure to return"); break;
		
	}
	
}

void ResetPointers(MenuContext CurrentMenuContext) {
	
	
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
