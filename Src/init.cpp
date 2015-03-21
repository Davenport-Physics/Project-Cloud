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
		
		return DelimitString(temp,':');
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

static int WindowHeight = 1024;
static int WindowWidth  = 768;
static int MaximumFPS   = 60;
	
static enum TextRendering RenderingType = BLENDED;
static enum MapType map                 = GENERATION;

static const int NumConfig = 6;
static bool (*ConfigFunction[NumConfig])(string) = {
	determine_window_height,
	determine_window_width,
	determine_rendering_type,
	determine_map_type,
	determine_max_fps,
	determine_controls
};

/*
 * TODO
 * 
 * For some reason the j is not being read in. It could have something to
 * do with the escape sequence. It might be best to just have escape and
 * enter as non-modifiable keys.
 * 
 * */
void InitConfigFile() {
	
	ifstream infile(ConfigPath.c_str());
	
	string temp;
	if (infile.good() == true) {
		
		for (int x = 0;x < NumConfig;x++) {
		
			temp = "";
			getline(infile, temp);
			cout << temp << "\n";
			if(!ConfigFunction[x](temp))
				continue;
			
		}
		
		infile.close();
		return;
		
	}
	infile.close();
	
	ofstream outfile(ConfigPath.c_str());
	
	outfile << "WindowHeight:1024\n";
	outfile << "WindowWidth:768\n";
	outfile << "Rendering:BLENDED\n";
	outfile << "MapType:GENERATION\n";
	outfile << "MaxFPS:60\n";
	outfile << "Controls:wsad" << (char)27 << "j" << "\\n\n";
	
	outfile.close();
	
}

bool determine_window_height(string str) {
	
	if (str.find("WindowHeight") != string::npos) {
		
		
		string temp = DelimitString(str, ':');
		WindowHeight = StringToInt(temp);
		
		return true;
		
	}
	
	return false;
	
}
bool determine_window_width(string str) {

	if (str.find("WindowWidth") != string::npos) {
	
		string temp = DelimitString(str, ':');
		WindowWidth = StringToInt(temp);
		
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
	
		MaximumFPS = StringToInt(DelimitString(str,':'));
		return true;
		
	}
	return false;
	
}

/*
 * TODO
 * 
 * This function is misbehaving badly.
 * 
 * */
bool determine_controls(string str) {
	
	if (str.find("Controls") != string::npos) {
	
		char *controls = new char[NUMCONTROLS];
		
		str = DelimitString(str, ':');
		cout << "str = " << str << "\n";
		strncpy(controls, str.c_str(), NUMCONTROLS);
		UserControls.set_controls_to_chars(controls);
		
		delete [] controls;
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
