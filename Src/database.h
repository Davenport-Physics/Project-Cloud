/*
 * database.h
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


#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <cstring>
#include <string>

#include <sqlite3.h>

enum {
	
	EXISTS = 0,
	DOESNOTEXIST
	
};

using std::string;
using std::cout;
using std::vector;
using std::strcpy;

class Database {
	
private:

	sqlite3 *db;
	sqlite3_stmt *stmt;
	
	bool HadError;
	
	void execute(char *sql, string IfError);

public:

	Database(string database);
	~Database();
	
	/*
	 * INSERT values INTO table
	 * 
	 * where values are structured as such "value,value,'char value'"
	 * 
	 * */
	void insert_data(string table , string values);
	
	/*
	 * 
	 * UPDATE table SET AttributeName=value or 'char value' WHERE AttributeName=value or 'char value'
	 * 
	 * */
	void update_data(string table, string set, string where);
	
	/*
	 * CREATE table(variables)
	 * 
	 * */
	void create_table(string table , string variables );
	
	/*
	 * DELETE values FROM table
	 * 
	 * */
	void delete_data(string table, string values);
	
	int check_if_table_exists(string table);
	
	vector <string> retrieve_data(string parameter , string table);
	
};

#endif

