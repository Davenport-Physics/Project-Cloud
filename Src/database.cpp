/*
 * database.cpp
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

#include "database.h"

Database::Database(string database) {
	
	this->HadError = false;
	
	char *dbname = (char *)database.c_str();
	
	int rc = sqlite3_open(dbname , &this->db);
	
	if ( rc != SQLITE_OK ) {
	
		cout << "There was an error opening database " << database;
		sqlite3_close(this->db);
		
		this->HadError = true;
		
	}
	cout << dbname << "\n";
	
}

void Database::insert_data( string table, string values ) {
	
	string command	= "INSERT INTO " + table + " VALUES(" + values + ")";
	char *sql		= (char *)command.c_str();
	
	execute(sql, "Could not insert data into table");
	
}

void Database::create_table( string table , string variables) {

	string command	= "CREATE TABLE " + table + "(" + variables + ")";
	char *sql		= (char *)command.c_str();
	
	execute(sql , "Could not create table");
	
	
}

void update_data(string table, string set, string where) {

	string command 	= "UPDATE " + table + "SET " + set + "WHERE " + where;
	char *sql		= (char *)command.c_str();
	
	execute(sql , "Could not update data"); 
	
}

void delete_data(string table , string values) {
	
	string command	= "DELETE " + values + "FROM " + table;
	char *sql		= (char *)command.c_str();
	
	execute(sql , "Could not delete data");
	
}

vector <string> Database::retrieve_data(string parameters, string table) {
	
	const char *error_message;

	string command	= "SELECT " + parameters + " FROM " + table;
	char *sql		= (char *)command.c_str();
	
	int rc			= sqlite3_prepare_v2(this->db , sql , -1 , &this->stmt , &error_message);
	
	vector<string> values;
	
	if (rc != SQLITE_OK) {
	
		cout << "Had some type of error reading data";
		
	} else {
	
		string str;
		
		int col_num = sqlite3_column_count(stmt);
		
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			
			str = "";
			for ( int x = 0; x < col_num;x++ ) {
				
				char *temp = (char *)sqlite3_column_text(stmt , x);
				str += temp;
				
				if (x < (col_num - 1)) {
					
					str += "|";
					
				}
				
			}
			values.push_back(str);
			
		}
		
	}

	return values;
}

int Database::check_if_table_exists(string table) {
	
	const char *err_message;

	string command 	= "SELECT * FROM " + table;
	char *sql		= (char *)command.c_str();
	
	int rc = sqlite3_prepare_v2(this->db , sql , -1 , &this->stmt , &err_message);
	
	if (rc != SQLITE_OK) {
	
		return DOESNOTEXIST;
		
	} else {
	
		return EXISTS;
		
	}
	
}

Database::~Database() {
	
	sqlite3_close(this->db);
	
}

//Private methods

void Database::execute( char *sql, string IfError ) {
	
	char *error_message;

	int rc = sqlite3_exec( this->db , sql , 0 , 0 , &error_message );
	
	if ( rc != SQLITE_OK ) {
	
		cout << IfError;
		
	}
	
}

