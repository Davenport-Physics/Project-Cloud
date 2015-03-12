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

static int WindowHeight;
static int WindowWidth;
	
static int MaximumFPS;
	
static enum TextRendering RenderingType;
static enum MapType map;

/*
 * TODO
 * 
 * There is a bug here. Probably because of the operating system macros.
 * It works perfectly fine if you just type the location of the config
 * file during the initialization of the ifstream/ofstream objects
 * 
 * */
void InitConfigFile() {
	
	ifstream infile(ConfigPath.c_str());
	
	//cout << ConfigPath.c_str();
	if (infile.good() == true) {
		
		string temp = "";
		
		getline(infile, temp);
		if (!determine_window_height(temp))
			WindowHeight = 1024;
		
		temp = "";
		getline(infile, temp);
		if(!determine_window_width(temp))
			WindowWidth = 768;
		
		temp = "";
		getline(infile, temp);
		if (!determine_rendering_type(temp))
			RenderingType = BLENDED;
		
		temp = "";
		getline(infile, temp);
		if (!determine_map_type(temp))
			map = GENERATION;
			
		temp = "";
		getline(infile, temp);
		if (!determine_max_fps(temp))
			MaximumFPS = 60;
		
		infile.close();
		return;
		
	}
	infile.close();
	
	ofstream outfile(ConfigPath.c_str());
	
	outfile << "WindowHeight:1024\n";
	outfile << "WindowWidth:768\n";
	outfile << "Rendering:BLENDED\n";
	outfile << "MapType:Generation\n";
	outfile << "MaxFPS:60\n";
	
	WindowHeight  = 1024;
	WindowWidth   = 768;
	RenderingType = BLENDED;
	map			  = GENERATION;
	MaximumFPS    = 60;
	
	outfile.close();
	
}

bool determine_window_height(string str) {
	
	if (str.find("WindowHeight") != string::npos) {
		
		
		string temp = return_right_string_by_delimiter(str, ':');
		WindowHeight = convert_string_to_int(temp);
		
		return true;
		
	}
	
	return false;
	
}
bool determine_window_width(string str) {

	if (str.find("WindowWidth") != string::npos) {
	
		string temp = return_right_string_by_delimiter(str, ':');
		WindowWidth = convert_string_to_int(temp);
		
		return true;
		
	}
	
	return false;
	
}
bool determine_rendering_type(string str) {

	if (str.find("Rendering") != string::npos) {
		
		if (str.find("BLENDED") != string::npos) {
		
			RenderingType = BLENDED;
			
		} else if (str.find("SHADED") != string::npos) {
			
			RenderingType = SHADED;
			
		} else if (str.find("FAST") != string::npos) {
		
			RenderingType = FAST;
			
		} else {
		
			return false;
			
		}
		
		
		return true;
		
	}
	
	return false;
	
}
bool determine_map_type(string str) {
	
	if (str.find("MapType") != string::npos) {
		
		if (str.find("GENERATION") != string::npos) {
		
			map = GENERATION;
			
		} else if (str.find("STATIC") != string::npos) {
		
			map = STATIC;
			
		} else {
		
			return false;
			
		}
	
		return true;
		
	}
	
	
	return false;
	
}
bool determine_max_fps(string str) {

	if (str.find("MaxFPS") != string::npos) {
	
		MaximumFPS = convert_string_to_int(return_right_string_by_delimiter(str,':'));
		return true;
	}
	return false;
}

int get_window_height() {

	return WindowHeight;
	
}

int get_window_width() {

	return WindowWidth;
	
}

int get_max_fps() {

	return MaximumFPS;
	
}

enum TextRendering get_rendering_type() {

	return RenderingType;
	
}

enum MapType get_map_type() {

	return map;
	
}
