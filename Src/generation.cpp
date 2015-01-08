/*
 * generation.cpp
 * 
 * Copyright 2014 Michael Davenport <Davenport.physics@gmail.com>
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


#include "generation.h"

Map::Map(int Number) {

	this->rows 		= 35 + rand()%60;
	this->columns	= 35 + rand()%60;
	this->Number	= Number;

	initialize();
	
	
}

Map::Map(int rows , int columns , int Number ) {
	
	this->rows		= rows;
	this->columns	= columns;
	this->Number	= Number;

	initialize();
	
}

Map::Map(int rows , int columns , int *firstpos , int *secondpos , char *map[]) {

	this->rows		= rows;
	this->columns	= columns;
	
	this->FirstPosition[0] = firstpos[0];
	this->FirstPosition[1] = firstpos[1];
	
	this->SecondPosition[0] = secondpos[0];
	this->SecondPosition[1] = secondpos[1];
	
	this->map = new char *[rows];
	
	for (int i = 0; i < rows;i++)
		this->map[i] = new char[columns];
		
	for (int y = 0;y < rows;y++)
		for (int x = 0;x < columns;x++)
			this->map[y][x] = map[y][x];
	
}

void Map::initialize() {
	
	this->sum = this->rows + this->columns;
	
	this->map = new char*[this->rows];
	
	for (int y = 0; y < this->rows;y++) {
	
		this->map[y] = new char[this->columns];
		
	}
	

	for (int y = 0; y < this->rows;y++)
		for (int x = 0;x < this->columns;x++)
			this->map[y][x] = '.';
			
	add_borders();
	add_holes();
	surround_holes();
	add_walls();
	add_gold();
	add_forward_backwards();
	add_save_point();
	
}

void Map::add_borders() {
	
	for (int y = 0;y < this->rows;y++) {
		
		this->map[y][0]				= '#';
		this->map[y][this->columns-1] = '#';
		
	}
	
	for (int x = 0;x < this->columns;x++) {
	
		this->map[0][x]		= '#';
		this->map[rows-1][x]	= '#';
		
	}
	
}

void Map::add_holes() {

	int numholes = rand()%((this->sum)/6);
	
	if (numholes == 0)
		return;
	
	int currentx , currenty;	
	for (int i = 0; i < numholes;i++) {
	
		currentx = currenty = 0;
		
		while (true) {
		
			get_random_location_by_bounds(&currentx,&currenty);
			
			try {
				
				if (this->map[currenty][currentx] != '#')
					break;
				
			} catch (exception& e) { continue; }
			
		}
		
		int holesize = 1 + rand()%20;
		int x,y;
		for (int j = 0; j < holesize;j++) {
		
			x = y = 0;
			
			try {
				
				while (true) {
					
					x = determine_next_position();
					y = determine_next_position();
					
					if ( this->map[currenty + y][currentx + x] != '#' )
						break;
					
				}
				
			} catch (exception& e) { continue; }
			
			currentx += x;
			currenty += y;
			
			this->map[currenty][currentx] = 'X';
			
		}
		
	}
	
}

void Map::surround_holes() {

	for (int y = 0; y < this->rows; y++) {
	
		for (int x = 0; x < this->columns; x++) {
			
			if (this->map[y][x] == 'X') {
				
				try {
				
					if (this->map[y+1][x] == '.')
						this->map[y+1][x] = '#';
				
				} catch (exception& e) { continue; }
				
				try {
					
					if (this->map[y-1][x] == '.')
						this->map[y-1][x] = '#';
					
				} catch (exception& e) { continue; }
				
				try {
					
					if (this->map[y][x+1] == '.')
						this->map[y][x+1] = '#';
					
				} catch (exception& e) { continue; }
				
				try {
					
					if (this->map[y][x-1] == '.')
						this->map[y][x-1] = '#';
					
				} catch (exception& e) { continue; }
				
			}
				
		}
		
	}
	
}

void Map::add_walls() {
	
	int numwalls = 2 + rand()%((this->sum)/2);
	
	int currentx , currenty;
	for (int i = 0; i < numwalls;i++) {
		
		currentx = currenty = 0;
		
		while (true) {
		
			get_random_location_by_bounds(&currentx,&currenty);
			
			if (this->map[currenty][currentx] != '#' && this->map[currenty][currentx] != 'X')
				break;
			
		}
		
		int up = 1 + rand() % 100;
		int right = 1 + rand() % 100;
		
		if (right <= 55)
			right = 0;
		else if ( abs( currentx - this->columns ) > this->columns/2 )
			right = 1;
		else if ( abs(currentx - this->columns ) < this->columns/2 )
			right = -1;
		else
			right = determine_next_position();
			
		
		if ( right != 0 && up > 70 )
			up = 0;
		else if ( abs( currenty - this->rows ) > this->rows/2 )
			up = 1;
		else if ( abs( currenty - this->rows ) < this->rows/2 )
			up = -1;
		else
			up = determine_next_position();
			
			
		int WallLength = 3+rand()%10;
		
		for (int z = 0; z < WallLength;z++) {
		
			currentx += right;
			currenty += up;
			
			try {
				
				if ( this->map[currenty][currentx] == '.' ) {
				
					this->map[currenty][currentx] = '#';
					
				} else {
				
					break;
					
				}
				
			} catch (exception& e) { break; }
			
		}
		
	}
	
}

void Map::add_gold() {

	int jackpot = 1 + rand()%100;
	
	int totalgold;
	
	if (jackpot >= 90) {
	
		totalgold = 10 + rand()%((this->sum)/2);
		
	} else {
		
		totalgold = 5 + rand()%((this->sum)/6);
	
	}
	
	int x,y;
	for (int i = 0;i < totalgold;i++) {
		
		while (true) {
		
			get_random_location_by_bounds(&x,&y);
		
			if (this->map[y][x] == '.')
				break;
		
		}
		this->map[y][x] = '+';
		
	}
	
}

//TODO for some reason first map is getting both forward and backward points
void Map::add_forward_backwards() {

	//backward <
	int x,y;
	
	while (true) {
		
		get_random_location_by_bounds(&x,&y);
			
		if (this->map[y][x] == '.' ) {
			
			if (determine_if_suitable_position(x,y)) {
				
				if (this->Number != -1) {
					
					this->map[y][x] = '<';
					
				}
				initialize_position(x , y , FirstPosition);
					
				break;
					
			}
				
		}
			
	}
	
	//forward >
	if (this->Number != NUM_MAPS) {
	
		while (true) {
		
			get_random_location_by_bounds(&x,&y);
			
			if (this->map[y][x] == '.') {
				
				if (determine_if_suitable_position(x,y)) {
				
					this->map[y][x] = '>';
					
					initialize_position(x , y , SecondPosition);
					
					break;
					
				}
				
			}
			
		}
		
	}
	
	
}

void Map::add_save_point() {

	int x,y;
	while (true) {
	
		get_random_location_by_bounds(&x , &y);
		
		if (determine_if_suitable_position(x,y) == true) {
		
			this->map[y][x] = 's';
			break;
			
		}
		
	}
	
}

void Map::initialize_position(int x , int y , int *position) {

	if (determine_if_suitable_position(x+1,y)) {
	
		position[0] = x+1;
		position[1] = y;
		
	} else if (determine_if_suitable_position(x-1,y)) {
	
		position[0] = x-1;
		position[1] = y;
		
	} else if (determine_if_suitable_position(x,y+1)) {
	
		position[0] = x;
		position[1] = y+1;
		
	} else if (determine_if_suitable_position(x,y-1)) {
	
		position[0] = x;
		position[1] = y-1;
		
	}
	
}

int Map::determine_next_position() {

	int next = rand() % 2;
	
	switch (next) {
	
		case 0: return -1; break;
		case 1: return 0; break;
		case 2: return 1; break;
		default: return 0; break;
		
	}
	
}
void Map::get_random_location_by_bounds(int *x, int *y) {

	*x = 1 + rand()%(this->columns - 2);
	*y = 1 + rand()%(this->rows - 2);
	
}

bool Map::determine_if_suitable_position(int x , int y) {
	
	try {
		
		if (this->map[y+1][x] != '#' || this->map[y-1][x] != '#'
			|| this->map[y][x+1] != '#' || this->map[y][x-1] != '#') {
					
			return true;
					
		}
		
	} catch (exception& e) {}
	
	return false;
	
}

void Map::print_map() {

	for (int y = 0; y < this->rows;y++) {
	
		for (int x = 0; x < this->columns;x++) {
		
			cout << this->map[y][x];
			
		}
		
		cout << endl;
		
	}
	
}
void Map::print_map_around_player(int bounds) {

	int InitialX	= (*this->x) - bounds;
	int FinalX		= (*this->x) + bounds;
	
	if (InitialX < 0)
		InitialX = 0;
	if (FinalX > this->columns)
		FinalX = this->columns;
		
	int InitialY	= (*this->y) - bounds;
	int FinalY		= (*this->y) + bounds;
		
	if (InitialY < 0)
		InitialY = 0;
	if (FinalY > this->rows)
		FinalY = this->rows;
		
	for (int y = InitialY; y < FinalY;y++) {
	
		for (int x = InitialX; x < FinalX;x++) {
		
			if (y == (*this->y) && x == (*this->x)) {
				
				cout << "@" << " ";
				
			} else if (this->map[y][x] == 'X') {
				
				cout << "  ";
				
			} else {
				
				cout << this->map[y][x] << " ";
				
			}
			
		}
		cout << endl;
		
	}
	
}

/*
 * Outputs something of this format
 * 
 * START(<x>,<y>)
 * <2D Map>
 * END(<Fx>,<Fy>)(<Sx>,<Sy>)
 * 
 * where attributes within greater than or less than signs are not literal
 * but instead are a value.
 * 
 * The values after START, are the dimensions of the 2D array.
 * 
 * The values after END, are the FirstPosition values followed by
 * the SecondPosition Values.
 * 
 * */
void Map::save_map(string filename) {

	ofstream out;
	
	out.open(filename.c_str(), ios_base::app);
	
	out << "START(" << this->columns << "," << this->rows << ")\n";
	for (int y = 0; y < this->rows;y++) {
	
		for (int x = 0; x < this->columns;x++) {
		
			out << this->map[y][x];
			
		}
		out << endl;
	}
	out << "END(" << this->FirstPosition[0] << "," << this->FirstPosition[1];
	out << ")";
	out <<  "(" << this->SecondPosition[0] << "," << this->SecondPosition[1];
	out << ")" << endl;
	
	out.close();
	
}

int * Map::get_first_position() {

	return FirstPosition;
	
}

int * Map::get_second_position() {

	return SecondPosition;
	
}

void Map::transition_to_new_map(int *x , int *y , int Direction) {
	
	this->x = x;
	this->y = y;
	
	if (Direction == FORWARD) {
	
		*this->x = FirstPosition[0];
		*this->y = FirstPosition[1];
		
	} else if (Direction == BACKWARD) {
	
		*this->x = SecondPosition[0];
		*this->y = SecondPosition[1];
		
	}
	
}

int Map::check_if_player_can_move(int x , int y) {
	
	switch (this->map[y][x]) {
	
		case '#':
		case 'X':
		
			return NO;
		
		break;
		
		case '+':  this->map[y][x] = '.'; return GOLD; break;
		case 's': return SAVE; break;
		default: return YES; break;
		
	}
	
}

int Map::get_rows() {

	return this->rows;
	
}

int Map::get_columns() {

	return this->columns;
	
}

string Map::convert_map_to_string() {
	
	string map = "";
	for (int y = 0;y < this->rows;y++) {
		
		map += string(this->map[y]);
		
		if (y < this->rows-1) {
		
			map += "~";
			
		}
		
	}
	
	return map;
}

Map::~Map() {
	
	delete [] this->map;
	
}
