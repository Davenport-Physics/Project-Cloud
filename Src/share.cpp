/*
 * share.cpp
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


#include "share.h"

//Potential for error, with typecast of long int to int.
int StringToInt(string line) {

	return (int)strtol( line.c_str() , NULL , 10 );
	
}

float StringToFloat(string line) {

	return strtof(line.c_str(), NULL);
	
}

string FloatToString(float var) {

	char buffer[512];

	snprintf(buffer, sizeof(buffer) , "%.2f" , var);
	
	return string(buffer);
	
}

vector<string> GetVectorByDelimiter(string str, char delimiter) {
	
	vector<string> strings;
	
	do {
		
		strings.push_back(str.substr(0 , str.find(delimiter)));
		
		str = str.substr(str.find(delimiter) + 1,str.length());
		
	} while (str.find(delimiter) != string::npos);
	
	return strings;
	
}

/*
 * GetCharsByDelimiter : string str, char delimiter
 * 
 * This function takes in a string that is formatted as such
 * a,b,c,d,... and returns a char array delimited by the passed delimiter.
 * 
 * WARNING
 * This is both a potentially expensive function call, and at the same time
 * can lead to a potential issue if for some reason the player decides to
 * use , as a control.
 * 
 * Also be sure to delete the passed char pointer.
 * 
 * 
 * */
char * GetCharsByDelimiter(string str, char delimiter) {
	
	vector<string> strings = GetVectorByDelimiter(str, delimiter);
	
	cout << strings[0] << "\n";
	cout << strings.size();
	char *chars = new char[strings.size()];
	for (unsigned int x = 0;x < strings.size();x++) {
	
		chars[x] = SingleCharStringToChar(strings[x]);
		
	}
	return chars;
	
}

char SingleCharStringToChar(string str) {

	if (str.length() > 2) {
		cout << "str = " << str << "\n";
		throw invalid_argument("String length larger than 2");
	}
		
	char ThisChar[1];
	
	strncpy(ThisChar, str.c_str(), 1);
	
	char temp = ThisChar[0];
	
	return temp;
	
}

string DelimitString(string str, char delimiter) {
	
	return str.substr(str.find(delimiter)+1, str.length());
	
}

