/*
 * generation.h
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


#ifndef GENERATION_H
#define GENERATION_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include "share.h"

#define NUM_MAPS 30

/*
 * Can the player move to this current spot? YES or NO
 * 
 * Also some specific attributes like, GOLD means there is gold at that
 * point and that the game should handle it.
 * 
 * */
enum {

	YES = 0,
	NO,
	GOLD,
	SAVE,
	FORWARD,
	BACKWARD
	
};

using namespace std;

class Map {
	
private:

	/*
	 * rows and columns are each variables that hold the amount of rows
	 * and columns the 2D char array will hold. The variable sum is
	 * the sum of the value of rows and columns.
	 * 
	 * */
	int rows, columns;
	int sum;
	
	/*
	 * Number is the variable that will hold this map's index within
	 * the vector located in main. It is used during map generation,
	 * in determination of whether there should be two portals, or just
	 * one specific one.
	 * 
	 * */
	int Number;
	
	
	/*
	 * FirstPosition is the position on the map where the player is
	 * initially located on each separate map. SecondPosition is the position
	 * the player will take upon re-entering a map using one of the
	 * portals.
	 * 
	 * */
	int FirstPosition[2];
	int SecondPosition[2];
	
	char **map;
	
	/*
	 * 
	 * pointers to the player's current location
	 * 
	 * */
	int *x;
	int *y;
	
	
	void initialize();
	
	void add_borders();
	void add_holes();
	void surround_holes();
	void add_walls();
	void add_gold();
	void add_forward_backwards();
	void add_save_point();
	//TODO Add chests, and npc's
	
	void get_random_location_by_bounds(int *x, int *y);
	void initialize_position(int x , int y, int *position);
	
	int determine_next_position();
	
	bool determine_if_suitable_position(int x, int y);
	
public:

	Map(int Number);
	Map(int rows , int columns , int Number);
	Map(int rows , int columns , int *firstpos , int *secondpos , char *map[]);
	~Map();
	
	int get_rows();
	int get_columns();
	int * get_first_position();
	int * get_second_position();
	int check_if_player_can_move(int x, int y);
	
	char ** get_map();
	
	void print_map();
	void print_map_around_player(int bounds);
	void save_map(string filename);
	void transition_to_new_map(int *x,int *y, int Direction);
	
	string convert_map_to_string();
	
};


#endif

