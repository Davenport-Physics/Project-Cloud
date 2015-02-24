/*
 * share.h
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

#ifndef SHARE_H
#define SHARE_H

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

#define MAXCOLUMNS 40
#define RESET_POSITION 0

/*
 * Converts integer to string.
 * 
 * */
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using std::cout;
using std::string;
using std::endl;
using std::vector;

template<int numrows,int numcolumns>
void print_2d_array(char (&array)[numrows][numcolumns]) {

	for ( int y = 0; y < numrows; y++ ) {
		
		for ( int x = 0; x < numcolumns; x++ ) {
		
			cout << array[y][x] << " ";
			
		}
		
		cout << endl;
		
	}
	
}

int convert_string_to_int(string line);

float convert_string_to_float(string line);

string convert_float_to_string(float var);

vector<string> delimit_string(string str, char delimiter);

#endif
