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
int convert_string_to_int(string line) {

	return (int)strtol( line.c_str() , NULL , 10 );
	
}

float convert_string_to_float(string line) {

	return strtof(line.c_str(), NULL);
	
}

string convert_float_to_string(float var) {

	char buffer[512];

	snprintf(buffer, sizeof(buffer) , "%.2f" , var);
	
	return string(buffer);
	
}

vector<string> delimit_string(string str, char delimiter) {
	
	vector<string> strings;
	
	do {
		
		strings.push_back(str.substr(0 , str.find(delimiter)));
		
		str = str.substr(str.find(delimiter) + 1,str.length());
		
	} while (str.find(delimiter) != string::npos);
	
	return strings;
	
}

