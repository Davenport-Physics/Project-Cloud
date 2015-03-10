//      mainmenu.h
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


#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "init.h"
#include "controls.h"
#include "share.h"
#include "engine.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::invalid_argument;


typedef enum MenuContext {
	
	MAINMENU = 0,
	NEWGAME,
	LOADGAME,
	SAVES,
	OPTIONS,
	CONTROLS,
	VIEWCONTROLS,
	CHANGECONTROLS,
	CREDITS,
	NONE
	
}MenuContext;

typedef struct PointerVars {
	
	int Dx, Dy;
	int Min_x, Min_y;
	int Max_x, Max_y;
	
} PointerVars;

typedef struct Pointer {
	
	int x, y;
	
} Pointer;

int show_saves(string *saves);

void ResetPointers(MenuContext CurrentMenuContext);
void SetMenuPointer(MenuContext CurrentMenuContext);
void RemoveExtraPointers(MenuContext CurrentMenuContext);
void HandleBasicInputMenu(enum ControlType, MenuContext CurrentMenuContext);

bool CheckPointerEquality(Pointer First, Pointer Second);

MenuContext UpdateMainMenu();
MenuContext UpdateOptionsMenu();
MenuContext UpdateControlsMenu();
MenuContext RunCredits();

MenuContext UpdateMenu(enum ControlType type, MenuContext (*MenuFunction)(), MenuContext CurrentMenuContext);

PointerVars GetCurrentPointerVars(MenuContext CurrentMenuContext);

#endif

