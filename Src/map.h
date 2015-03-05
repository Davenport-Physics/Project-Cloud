/*
 * map.h
 * 
 * Copyright 2014-2015 Michael Davenport <Davenport.physics@gmail.com>
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


#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include "share.h"
#include "engine.h"

#define NUM_MAPS 30

using namespace std;

enum MapType {
	
	STATIC = 0,
	GENERATION
	
};

/*
 * Can the player move to this current spot? YES or NO
 * 
 * Also some specific attributes like, GOLD means there is gold at that
 * point and that the game should handle it.
 * 
 * */
enum MapVars {

	YES = 0,
	NO,
	GOLD,
	SAVE,
	FORWARD,
	BACKWARD
	
};

struct Transition {
	
	int x;
	int y;
	
	string name;
	
};

/*
 * Removed first and last position, for the transition points. During transition,
 * the map will just place the player ontop of the transition marker. This
 * may need to be re-added later when the game is allowed to refresh without
 * player input.
 * 
 * */
class Map {

private:

	int rows, columns;
	
	int *x, *y;
	
	char **map;
	string name;
	
	int NumTransitionPoints;
	struct Transition *points;

public:

	Map(int rows, int columns, int NumTransitionPoints, struct Transition *point, char *map[]);
	~Map();
	
	int get_rows();
	int get_columns();
	
	enum MapVars check_if_player_can_move(int x, int y);
	
	char ** get_map();
	
	void save_map(string filename);
	void print_map_around_player(int bounds);
	string transition_to_new_map(int *x, int *y);
	
	
};

class MapGenerator {
	
private:

	/*
	 * Number is the variable that will hold this map's index within
	 * the vector located in main. It is used during map generation,
	 * in determination of whether there should be two portals, or just
	 * one specific one.
	 * 
	 * */
	int Number;

	/*
	 * rows and columns are each variables that hold the amount of rows
	 * and columns the 2D char array will hold. The variable sum is
	 * the sum of the value of rows and columns.
	 * 
	 * */
	int rows, columns;
	int sum;
	
	/*
	 * 
	 * pointers to the player's current location
	 * 
	 * */
	int *x;
	int *y;
	
	char **map;
	
	string name;
	
	int NumTransitionPoints;
	struct Transition *points;
	
	
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
	
	int determine_next_position();
	
	bool determine_if_suitable_position(int x, int y);
	
public:

	MapGenerator(int Number);
	MapGenerator(int rows , int columns , int Number);
	~MapGenerator();
	
	Map get_map_object();
	Map *get_map_object_heap();
	
};


#endif

