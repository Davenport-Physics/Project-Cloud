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

Config UserConfig;

string CheckForSaves(string filename) {

	ifstream infile(filename.c_str());
	
	string temp;
	if (infile.good()) {
		
		getline(infile, temp);
		infile.close();
		
		return return_right_string_by_delimiter(temp,':');
	}
	infile.close();
	
	return "empty";
	
}

Player * load_game(string filename, vector<Map *> *maps) {
	
	ifstream infile(filename.c_str());
	
	
	
	infile.close();
	
	return NULL;
	
}

#if __unix

static const string ConfigPath = "Data/config";

#elif __WIN32

static const string ConfigPath = "Data\\config";

#endif

Config::Config() {
	
	ifstream infile(ConfigPath.c_str());
	
	if (infile.good() == true) {
	
		string temp;
		
		getline(infile, temp);
		if (!determine_window_height(temp))
			this->WindowHeight = 1024;
		
		temp = "";
		getline(infile, temp);
		if(!determine_window_width(temp))
			this->WindowWidth = 768;
		
		temp = "";
		getline(infile, temp);
		if (!determine_rendering_type(temp))
			this->RenderingType = BLENDED;
		
		temp = "";
		getline(infile, temp);
		if (!determine_map_type(temp))
			this->map = GENERATION;
			
		temp = "";
		getline(infile, temp);
		if (!determine_max_fps(temp));
			this->MaximumFPS = 60;
		
		infile.close();
		return;
		
	}
	infile.close();
	
	ofstream outfile("Data/config");
	
	outfile << "WindowHeight:1024\n";
	outfile << "WindowWidth:768\n";
	outfile << "Rendering:BLENDED\n";
	outfile << "MapType:Generation\n";
	outfile << "MaxFPS:60\n";
	
	this->WindowHeight  = 1024;
	this->WindowWidth   = 768;
	this->RenderingType = BLENDED;
	this->map			= GENERATION;
	this->MaximumFPS    = 60;
	
	outfile.close();
	
}

bool Config::determine_window_height(string str) {
	
	if (str.find("WindowHeight") != string::npos) {
		
		
		string temp = return_right_string_by_delimiter(str, ':');
		this->WindowHeight = convert_string_to_int(temp);
		
		return true;
		
	}
	
	return false;
	
}
bool Config::determine_window_width(string str) {

	if (str.find("WindowWidth") != string::npos) {
	
		string temp = return_right_string_by_delimiter(str, ':');
		this->WindowWidth = convert_string_to_int(temp);
		
		return true;
		
	}
	
	return false;
	
}
bool Config::determine_rendering_type(string str) {

	if (str.find("Rendering") != string::npos) {
		
		if (str.find("BLENDED") != string::npos) {
		
			this->RenderingType = BLENDED;
			
		} else if (str.find("SHADED") != string::npos) {
			
			this->RenderingType = SHADED;
			
		} else if (str.find("FAST") != string::npos) {
		
			this->RenderingType = FAST;
			
		} else {
		
			return false;
			
		}
		
		
		return true;
		
	}
	
	return false;
	
}
bool Config::determine_map_type(string str) {
	
	if (str.find("MapType") != string::npos) {
		
		if (str.find("GENERATION") != string::npos) {
		
			this->map = GENERATION;
			
		} else if (str.find("STATIC") != string::npos) {
		
			this->map = STATIC;
			
		} else {
		
			return false;
			
		}
	
		return true;
		
	}
	
	
	return false;
	
}
bool Config::determine_max_fps(string str) {

	if (str.find("MaxFPS") != string::npos) {
	
		this->MaximumFPS = convert_string_to_int(return_right_string_by_delimiter(str,':'));
		return true;
	}
	return false;
}

int Config::get_window_height() {

	return this->WindowHeight;
	
}

int Config::get_window_width() {

	return this->WindowWidth;
	
}

int Config::get_max_fps() {

	return this->MaximumFPS;
	
}

enum TextRendering Config::get_rendering_type() {

	return this->RenderingType;
	
}

enum MapType Config::get_map_type() {

	return this->map;
	
}
