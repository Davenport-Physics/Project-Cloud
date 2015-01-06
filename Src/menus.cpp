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
	
	system("clear");
	
	while (true) {
		
		MainArray[y][x] = '>';
		
		print_2d_array(MainArray);
		
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


int options() {

char OptionsArray[5][10] = 
{{' ','C','o','n','t','r','o','l','s',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ','C','r','e','d','i','t','s',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};
	
	system("clear");

	int x = 0;
	int y = 0;
	int yo = y;
	
	while ( true ) {
		
		OptionsArray[y][x] = '>';
		
		print_2d_array(OptionsArray);
		
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
		system("clear");
		
	}
	return -1;
}

int show_saves(string *saves) {
	
	int YPosition = 0;
	
	char command;
	
	system("clear");
	while (true) {
		
		for (int y = 0;y < 3;y++) {
		
			if (YPosition == y) {
				
				cout << "> " << saves[y] << "\n\n";
				
			} else {
			
				cout << "  " << saves[y] << "\n\n";
				
			}
			
		}
		
		command = mygetch();
		switch(UserControls.check_control(command)) {
		
			case ENTER: return YPosition; break;
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
		
		system("clear");
	
	}

	
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
	
	system("clear");
	
	std::cout << "Credits" << std::endl;
	std::cout << "LP-Michael Davenport" << std::endl;
	std::cout << "HP-Alex Fatum" << std::endl;
	std::cout << "SAG-Max Mitchell" << std::endl;
	std::cout << std::endl;
	std::cout << "Special thanks to:" << std::endl;
	std::cout << "James Thomas" << std::endl;
	std::cout << "Linteg" << std::endl;
	std::cout << "Music by:" << std::endl;	
	std::cout << "Title1 - Max Mitchell" << std::endl;
	std::cout << "map2 - Midnight cloud - Max Mitchell" << std::endl;
	std::cout << "map1 - Waltz into the moonlight - tryad" << std::endl;
	
	std::cin.get();
	
}
