//      player.cpp
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

#include "init.h"

/*
 * Requires a file name to be sent to it, and then it checks to
 * see if it's available. If it is available, it returns a string of the
 * player's name. If it isn't available, then it returns a string "empty"
 * 
 * */
string check_for_saves(string filename) {	
	
	ifstream file;
	
	file.open(filename.c_str(), ios_base::in);
	
	if (!file.is_open()) {
		
		return "empty";
		
	} else {
		
		int index;
		string line;
		
		while (file >> line) {
		
			index = line.find("name");
			
			if (index != -1) {
			
				index = line.find("=");
				
				return line.substr( index+1 , line.length());
				
			}
			
		}
		
	}
	return "empty";
	
}
string check_for_saves_db(string filename) {
	
	Database db(filename);
	
	vector<string> lines = db.retrieve_data("name","Player");
	
	if (lines.size() == 0) {
	
		return "empty";
		
	} else {
	
		return lines[0];
		
	}
	
	return "empty";
	
}
/*
 * each line should be formatted as such
 * 
 * <attribute>=<variable> where attribute is a string, and variable could be
 * a string, integer, a combination of integers separated by a comma, or a float.
 * 
 * 
 * TODO BUG. Probably due to substrings. I had to modify some code above
 * by adding + 1 to the index found using str.find() when making a substring.
 * 
 * This removes the character within the substring
 * */
Player * load_game(string filename , vector<Map *> *maps) {
	
	character player;

	ifstream file(filename.c_str());
	
	/*if (!file.is_open()) {
	
		exit(EXIT_FAILURE);
		
	}*/
	
	load_player_vars(&player , &file);
	load_maps(&player , &file , maps);
	
	file.close();
	
	return new Player(player);
	
}

void load_player_vars(character *player , ifstream *file) {
	
	string line , temp;
	
	*file >> line;
	player->name = line.substr(line.find("=") , line.length());
	
	for (int x = 0; x < 8;x++) {
	
		*file >> line;
		temp = line.substr( line.find("=") + 1, line.length() );
		
		switch (x) {
		
			case 0: player->PlayerHealth	= convert_string_to_int(temp); break;
			case 1: player->MaxHealth		= convert_string_to_int(temp); break;
			case 2: player->PlayerLevel		= convert_string_to_int(temp); break;
			case 3: player->exp				= convert_string_to_int(temp); break;
			case 4: player->attack			= convert_string_to_int(temp); break;
			case 5: player->accuracy		= convert_string_to_int(temp); break;
			case 6: player->MapIndex		= convert_string_to_int(temp); break;
			case 7: player->gold			= convert_string_to_int(temp); break;
			
		}
		
	}
	
	for (int x = 0; x < 3;x++) {
	
		*file >> line;
		temp = line.substr(line.find("=") + 1 , line.length());
		
		switch (x) {
		
			case 0: player->Mana		= convert_string_to_float(temp); break;
			case 1: player->MaxMana		= convert_string_to_float(temp); break;
			case 2: player->ManaRegen	= convert_string_to_float(temp); break;
			
		}
		
	}

	//Coordinates
	*file >> line;
	temp = line.substr(line.find("=") + 1, line.length());
	
	int index	= temp.find(":");
				
	player->x	= convert_string_to_int( temp.substr(0,index) );
	player->y	= convert_string_to_int( temp.substr( index + 1 , temp.length() ) );
	
}

void load_maps(character *player , ifstream *file , vector<Map *> *maps) {
		
	int index 	= 0;
	unsigned int row = 0, column = 0;
	
	int firstpos[2];
	int secondpos[2];

	string line;
	string temp;
	
	vector<string> MapVector;
	
	int tempindex;
	while ( *file >> line ) {
	
		if (line.find("START") != string::npos) {
			
			temp		= line.substr( 6 , line.length() );
			tempindex	= temp.find(",");
			
			column	= convert_string_to_int( temp.substr(0 , tempindex) );
			row		= convert_string_to_int( temp.substr(tempindex + 1 , temp.length() - 1) );
			
			
			//TODO
		} else if (line.find("END") != string::npos) {
			
			temp = line.substr( 4 , line.length() );
			
			string first	= temp.substr( 0 , temp.find(")"));
			string second	= temp.substr( temp.find(")") + 1, temp.length() );
			second			= temp.substr(1 , temp.find(")") - 1 );
			
			firstpos[0] = convert_string_to_int(first.substr(0 , first.find(",")));
			firstpos[1] = convert_string_to_int(first.substr(first.find(",") + 1 , first.length()));
			
			secondpos[0] = convert_string_to_int(second.substr(0 , second.find(",")));
			secondpos[1] = convert_string_to_int(second.substr(second.find(",") + 1, second.length()));
			
			char **map = new char*[row];
			
			for (unsigned int y = 0;y < row;y++) {
			
				map[y] = new char[column];
				
			}
			
			for (unsigned int y = 0; y < row;y++) {
			
				string line = MapVector[y];
				for (unsigned int x = 0; x < column;x++) {
				
					map[y][x] = line[x];
					
				}
				
			}
			
			(*maps)[index] = new Map(row , column , firstpos , secondpos , map);
			
			index++;
			MapVector.erase(MapVector.begin() , MapVector.end());
			
			delete [] map;
			
		} else {
		
			if (line.length() == column) {
		
				MapVector.push_back(line);
				
			} else {
			
				cout << "Error!" << endl;
				cout << "line.length() " << line.length() << " != column " << column << endl;
				
			}
			
		}
		
	}
	
}

Player * new_game(string filename, vector<Map *> *maps) {
	
	string name;
	cout << "Please enter your name -> ";
	getline(cin , name);
	
	for ( int x = 0; x < NUM_MAPS; x++ ) {
	
		( *maps )[x] = new Map(x);
		
	}
	
	return new Player(name);

}

void save_game( string filename , Player *player , vector<Map *> maps ) {
	
	character vars = player->get_character_vars();
	
	ofstream out(filename.c_str());
	
	out << "name=" << vars.name << endl;
	out << "player_health=" << vars.PlayerHealth << endl;
	out << "max_health=" << vars.MaxHealth << endl;
	out << "level=" << vars.PlayerLevel << endl;
	out << "exp=" << vars.exp << endl;
	out << "attack=" << vars.attack << endl;
	out << "accuracy=" << vars.accuracy << endl;
	out << "map_index=" << vars.MapIndex << endl;
	out << "gold=" << vars.gold << endl; 
	out << "player_mana=" << vars.Mana << endl;
	out << "max_mana=" << vars.MaxMana << endl;
	out << "mana_regen=" << vars.ManaRegen << endl;
	out << "coordinates=" << vars.x << ":" << vars.y << endl;
	
	out.close();
	
	for (unsigned int x = 0; x < maps.size();x++) {
	
		maps[x]->save_map(filename);
		
	}
	cout << "Saved game" << endl;
	
}

static string tables[] = {"Player","Map"};
static string variables[] = 
{"Name TINYTEXT,Health INT,MaxHealth INT,Level INT,Exp INT,Attack INT,Accuracy INT,MapIndex INT,Gold INT,Mana DOUBLE,MaxMana DOUBLE,ManaRegen DOUBLE",
	
 "Id INT,NumRows INT,NumColumns INT,FirstX INT,FirstY INT,SecondX INT, SecondY INT,Map TEXT"};
void save_game_db(string filename, Player *player , vector<Map *> *maps) {
	
	Database db(filename);
	
	if (db.check_if_table_exists("Player") != EXISTS ) {
	
		db.create_table(tables[0], variables[0]);
		db.create_table(tables[1], variables[1]);
		
		db.insert_data(tables[0], convert_player_vars_to_string(player));
		
		for (unsigned int x = 0; x < (*maps).size();x++) {
		
			db.insert_data(tables[1] , convert_map_vars_to_string(x,(*maps)[x]));
			
		}
		
	} else {
		
		
		
	}
	
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
	
	char MapArray[map->get_rows()][map->get_columns()];
	
	values += "\'";
	for (int y = 0;y < map->get_rows();y++) {
	
		values += string(MapArray[y]) + "\n";
		
	}
	values += "\'";
	
	
	return values;
	
}
