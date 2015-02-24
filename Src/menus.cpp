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

static const int height = 10;
static const int width = 22;
	
int main_menu() {
	
char MainArray[height][width] = {
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
	
	int x = 3;
	int y = 5;
	int oldx = x;
	int oldy = y;
	string load = "";
	
	while (true) {
		
		MainArray[y][x] = '>';
		
		draw_2d_stack_array(MainArray,&draw_2d_array);
		
		//print_2d_array(MainArray);
		
		char command = mygetch();
		switch (UserControls.check_control(command)) {
		
			case UP:
			
				y -= 2;
				x -= 2;
				
			break;
			
			case DOWN:
			
				y += 2;
				x += 2;
			
			break;
			
			case QUIT:
			
				cout << "Goodbye" << endl;
				return EXITGAME;
				
			break;
			
			case ENTER:
			
				if ( oldy == 5 && oldx == 3 ) {
				
					return NEWGAME;
				
				} else if ( oldy == 7 && oldx == 5 ) {
				
					return LOADGAME;
				
				} else {
			
					return OPTIONS;
				
				}
				
			break;
			
			default: cout << command << endl;
			
		}
		
		
		if (y <= 3 || y >= 10) {
			
			x = oldx;
			y = oldy;
			
		} else {
			
			MainArray[oldy][oldx] = ' ';
			oldx = x;
			oldy = y;
			
		}
		
		system("clear");	
		
	}
	
}


/*
 * TODO Add music option to increase/decrease/mute volume
 * 
 * */
int options() {

char OptionsArray[5][10] = 
{{' ','C','o','n','t','r','o','l','s',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ','C','r','e','d','i','t','s',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

	int x = 0;
	int y = 0;
	int yo = y;
	
	while ( true ) {
		
		OptionsArray[y][x] = '>';
		
		draw_2d_stack_array(OptionsArray, &draw_2d_array);
		
		char command = mygetch();
		switch (UserControls.check_control(command)) {
			
			case '\n':
			
				if ( y == 0 )
				
					return CONTROLS;
					
				else if ( y == 2 )
				 
					return CREDITS;
					
			break;
			
			case UP: y -= 2; break;
			case DOWN: y += 2; break;
			case QUIT: return QUIT; break; 
			
		}
		
		if (y < 0 || y > 2 ) {
			
			y = yo;
			
		} else {
			
			OptionsArray[yo][x] = ' ';
			yo = y;
			
		}
		
	}
	return -1;
}

int show_saves(string *saves) {
	
	int YPosition = 0;
	
	/*
	 * Potential for issue if the user has a really large name;
	 * 
	 * */
	char **SavesArray = new char *[3];
	for (int y = 0;y < 3;y++) {
	
		SavesArray[y] = new char[64];
		
		memset(SavesArray[y], ' ', 64);
		
		SavesArray[y][63] = '\0';
	}
	
	while (true) {
		
		for (int y = 0;y < 3;y++) {
			
			if (YPosition == y) {
				
				string temp = "> " + saves[y];
				strncpy(SavesArray[y], temp.c_str(), 63);
				
			} else {
			
				strncpy(SavesArray[y], saves[y].c_str(), 63);
				
			}
			
		}
		
		draw_2d_array(SavesArray, 3);
		
		switch(UserControls.get_input()) {
		
			case ENTER: return YPosition; break;
			case QUIT: return -1; break;
			case UP:
			
				if (YPosition > 0) {
				
					YPosition--;
					
				}
				
			break;
			case DOWN:
			
				if (YPosition < 2) {
				
					YPosition++;
					
				}
			
			break;
			
		}
	
	}

	delete [] SavesArray;
	
}

void controls() {
	
	cout << "Default Controls:" << endl;
	cout << "w,a,s,d - Movement" << endl;
	cout << "q - quit" << endl;
	cout << "h - heal" << endl;
	cout << "j - journal" << endl;
	cout << endl;
	cout << "Press enter to continue" << endl;
	
	cin.get();
	system("clear");

}

void credits() {
	
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


	draw_2d_stack_array(CreditsArray, &draw_animation_bottom_top);
	
}
