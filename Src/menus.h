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
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <vector>

#include "init.h"
#include "controls.h"
#include "mygetch.h"
#include "share.h"
#include "engine.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;


enum MenuContext {
	
	MAINMENU = 0,
	SAVES,
	CONTROLS,
	OPTIONS,
	CREDITS,
	NONE
	
};

int show_saves(string *saves);

void options();
void credits();
void controls();
void main_menu();

void ResetPointers();
void UpdatePointer(enum ControlType);
void UpdateMenu();

#endif

