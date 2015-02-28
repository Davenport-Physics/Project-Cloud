//      init.cpp
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
//      
//      

#include "init.h"

string check_for_saves_db(string filename) {
	
	if (check_if_database_exists(filename)) {
	
		Database db(filename);
	
		vector<string> lines = db.retrieve_data("Player","name");
	
		if (lines.size() == 0) {
	
			return "empty";
		
		} else {
	
			return lines[0];
		
		}
		
	}
	
	return "empty";
	
}

Player * new_game(string filename, vector<Map *> *maps) {
	
	string name = "";
	/*
	 * TODO
	 * 
	 * Backspace does not work, so most likely this will be
	 * handled by a specific renderer function call.
	 * 
	 * */
	char c;
	clear_screen();
	draw_string("Please enter your name -> " + name);
	while ((c = get_raw_input()) != '\n') {
		
		if (c == 0x7f) {
		
			name = name.substr(0, name.length()-1);
			
			
		} else {
			
			name += c;
		
		}
		clear_screen();
		draw_string("Please enter your name -> " + name);
		
	}
	
	
	for ( int x = 0; x < NUM_MAPS; x++ ) {
	
		( *maps )[x] = new Map(x);
		
	}
	
	return new Player(name);

}

static string tables[] = {"Player","Map"};
Player * load_game_db(string filename, vector<Map *> *maps) {

	Database db(filename);
	character PlayerVars;

	//TODO Might be faster to send a pointer of this vector
	vector<string> player = db.retrieve_data(tables[0],"*");
	if (player.size() == 1) {
		
		player = delimit_string(player[0] , '|');
		
	} else {
	
		cout << "More than one player string found\n";
		
		return new Player("Error");
		
	}
	if (load_player_vars_db(&PlayerVars , player ) == FAILURE) {
	
		cout << "Short on Vectors\n";
		return new Player("Error");
		
	}
	
	//TODO Might be faster to send a pointer of this vector
	vector<string> MapStrings = db.retrieve_data(tables[1],"*");
	if (load_maps_db(maps , MapStrings) == FAILURE) {
	
		cout << "Something went wrong loading the maps";
		return new Player("Error");
		
	}
	
	return new Player(PlayerVars);
	
	
}
SuccessEnum load_player_vars_db(character *player , vector<string> str) {
	
	if (str.size() == NUM_ATTRIBUTES ) {
		
		player->name 			= str[0];
		player->PlayerHealth 	= atoi(str[1].c_str());
		player->MaxHealth		= atoi(str[2].c_str());
		player->PlayerLevel		= atoi(str[3].c_str());
		player->exp				= atoi(str[4].c_str());
		player->attack			= atoi(str[5].c_str());
		player->accuracy		= atoi(str[6].c_str());
		player->MapIndex		= atoi(str[7].c_str());
		player->gold			= atoi(str[8].c_str());
		player->Mana			= atof(str[9].c_str());
		player->MaxMana			= atof(str[10].c_str());
		player->ManaRegen		= atof(str[11].c_str());
		
		return SUCCESS;
		
	}
	
	return FAILURE;
	
}

SuccessEnum load_maps_db(vector<Map *> *maps , vector<string> str) {
	
	vector<string> StringDelimited;
	int rows , columns;
	int FirstPos[2], SecondPos[2];
	
	char **CharMap = NULL;
	for (unsigned int y = 0;y < str.size(); y++) {
		
		StringDelimited = delimit_string(str[y] , '|');
		
		rows 	= atoi(str[1].c_str());
		columns	= atoi(str[2].c_str());
		
		FirstPos[0]	= atoi(str[3].c_str());
		FirstPos[1]	= atoi(str[4].c_str());
		
		SecondPos[0] = atoi(str[5].c_str());
		SecondPos[1] = atoi(str[6].c_str());
		
		CharMap = new char*[rows];
		for (int i = 0; i < rows;i++)
			CharMap[i] = new char[columns];
			
		vector<string> temp = delimit_string(str[7],'~');
		
		for (unsigned int i = 0;i < temp.size();i++) {
		
			for (int x = 0;x < columns;x++) {
			
				CharMap[i][x] = temp[i][x];
				
			}
			
		}
		(*maps)[y] = new Map(rows , columns , FirstPos , SecondPos , CharMap);
			
		delete [] CharMap;
		
		return SUCCESS;
		
	}
	
	return FAILURE;
	
}

static string variables[] = 
{"Name TINYTEXT,Health INT,MaxHealth INT,Level INT,Exp INT,Attack INT,Accuracy INT,MapIndex INT,Gold INT,Mana DOUBLE,MaxMana DOUBLE,ManaRegen DOUBLE",
	
 "Id INT,NumRows INT,NumColumns INT,FirstX INT,FirstY INT,SecondX INT, SecondY INT,CharMap TEXT"};
void save_game_db(string filename, Player *player , vector<Map *> maps) {
	
	
	Database *db = new Database(filename);
	draw_append_string("Saving...");
	
	if (db->check_if_table_exists("Player") == EXISTS ) {
	
		delete db;
		if (!delete_file(filename)) {
		
			return;
			
		}
	
	}
	
	db = new Database(filename);
	
	db->create_table(tables[0], variables[0]);
	db->create_table(tables[1], variables[1]);
		
	db->insert_data(tables[0], convert_player_vars_to_string(player));
		
	for (unsigned int x = 0; x < maps.size();x++) {
		
			db->insert_data(tables[1] , convert_map_vars_to_string(x,maps[x]));
			
	}
	
	delete db;
	
	draw_append_string("Finished Saving");
	
}

string convert_player_vars_to_string(Player *player) {
	
	string values = "\'" + player->vars.name + "\'" + "," + SSTR(player->vars.PlayerHealth);
	
	values += "," + SSTR(player->vars.MaxHealth) + "," + SSTR(player->vars.PlayerLevel);
	values += "," + SSTR(player->vars.exp) + "," + SSTR(player->vars.attack);
	values += "," + SSTR(player->vars.accuracy) + "," + SSTR(player->vars.MapIndex);
	values += "," + SSTR(player->vars.gold) + ",";
	
	char buffer[512];
	
	snprintf(buffer, sizeof(buffer) , "%f,%f,%f" , player->vars.Mana , player->vars.MaxMana , player->vars.ManaRegen);
	
	values += string(buffer);
	
	return values;
	
}
string convert_map_vars_to_string(unsigned int index,Map *map) {

	string values = SSTR(index) + "," + SSTR(map->get_rows());
	
	values += "," + SSTR(map->get_columns());
	
	int *pos = map->get_first_position();
	for (int x = 0; x < 2; x++) {
	
		values += "," + SSTR(pos[0]) + "," + SSTR(pos[1]);
		pos = map->get_second_position();
	}
	
	values += ",\'";
	values += map->convert_map_to_string();
	values += "\'";
	
	return values;
	
}
