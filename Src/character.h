/*
 * player.h
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

#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <cstdlib>

#include "share.h"
#include "engine.h"

#define NUM_ATTRIBUTES 12

using std::string;
using std::cout;

typedef enum PlayerAttributes {

	PLAYERHEALTH = 0,
	MAXHEALTH,
	PLAYERLEVEL,
	EXP,
	ATTACK,
	ACCURACY,
	COORDINATES,
	NAME,
	MANA,
	MAXMANA,
	MANAREGEN
	
} PlayerEnum;

typedef struct playervars {
	
	int PlayerHealth , MaxHealth;
	int PlayerLevel;
	int exp;
	int gold;
	
	int attack;
	int accuracy;
	
	int x , y;
	
	int MapIndex;
	
	string name;
	
	float Mana, MaxMana, ManaRegen;
	
} character;

//TODO. possible change character vars to private, and write getter setter variables.
class Player {


public:

	character vars;
	
	Player(string name);
	Player(character vars);
	~Player();
	
	int health_regeneration();
	int calculate_damage();
	
	void add_random_gold();
	void check_if_leveled_up();
	void reset_positions();
	
	character get_character_vars();
	
};

class Program : public Player {
	
	
	
};

int determine_attribute(string line);

#endif
