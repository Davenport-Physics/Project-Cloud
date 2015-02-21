/*
 * player.cpp
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

#include "character.h"

static int ExpPerLevel[30] = 
{25, 50, 75, 125, 200, 325, 525, 850, 1375, 
2225, 3600, 5825, 9425, 15250, 24675, 39925, 
64600, 104525, 169125, 273650, 442775, 716425, 
1159200, 1875625, 3034825, 4910450, 7945275, 
12855725, 20801000, 33656725};

Player::Player(string name) {
	
	this->vars.name			= name;
	this->vars.PlayerHealth = 10;
	this->vars.MaxHealth	= 10;
	
	this->vars.PlayerLevel	= 1;
	
	this->vars.attack		= 0;
	this->vars.accuracy		= 0;
	
	this->vars.Mana			= 3.0;
	this->vars.MaxMana		= 3.0;
	this->vars.ManaRegen	= 0.1;
	
	this->vars.x			= 0;
	this->vars.y			= 0;
	
	this->vars.MapIndex		= 0;
	this->vars.gold			= 0;
	
}

Player::Player(character vars) {
	
	this->vars = vars;
	
	
	
}

Player::~Player() {
	
	
	
}

int Player::health_regeneration() {
	
	return (this->vars.PlayerLevel + rand() % (7 + this->vars.PlayerLevel));
	
}

int Player::calculate_damage() {
	
	this->vars.accuracy = (1 + rand() % 100);
	
	if (this->vars.accuracy < 7 || this->vars.accuracy > 92) {
		
		return (5 + rand() % (15 + this->vars.PlayerLevel + this->vars.attack));
		
	} else {
		
		return (1 + rand() % (5 + this->vars.PlayerLevel + this->vars.attack));
		
	}
	
}

void Player::add_random_gold() {

	int gold = (1 + rand() % 15);
	
	cout << "Received " << gold << " gold pieces!\n"; 

	this->vars.gold += gold;
	
}

void Player::check_if_leveled_up() {

	if ( ExpPerLevel[this->vars.PlayerLevel] <= this->vars.exp ) {
	
		this->vars.PlayerLevel++;
		
		cout << "Leveled up!";
		
	}
	
}

void Player::reset_positions() {
	
	this->vars.x = RESET_POSITION;
	this->vars.y = RESET_POSITION;
	
}

character Player::get_character_vars() {
	
	return this->vars;
	
}

int determine_attribute(string line) {

	if (line.find("name") != string::npos)
		return NAME;
	else if (line.find("player_health") != string::npos)
		return PLAYERHEALTH;
	else if (line.find("max_health") != string::npos)
		return MAXHEALTH;
	else if (line.find("level") != string::npos)
		return PLAYERLEVEL;
	else if (line.find("exp") != string::npos)
		return EXP;
	else if (line.find("attack") != string::npos)
		return ATTACK;
	else if (line.find("player_mana") != string::npos)
		return MANA;
	else if (line.find("max_mana") != string::npos)
		return MAXMANA;
	else if (line.find("mana_regen") != string::npos)
		return MANAREGEN;
	else if (line.find("coordinates") != string::npos)
		return COORDINATES;
	else
		return -1;
	
}
