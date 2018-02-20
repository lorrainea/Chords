/**
    Copyright (C) 2018 Lorraine A.K. Ayad, Solon P. Pissis

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unordered_map>
#include <fstream>
#include <float.h>
#include "chords.h"

using namespace std;

unsigned int create_int_seqs( unsigned char ** dictionary, unsigned char * seq, unsigned int ** dictionary_array, unsigned int * seq_array, unordered_map<string, int> mapping, unsigned int num_dic, unsigned int * dictionary_size, unsigned int * total_dictionary_length )
{ 
	string note = "";
	int count = 2;

	for(int i=0; i<strlen( (char*) seq ); i++ )
	{

		if( seq[i] != ',' )	
		{
			string chr( 1, seq[i] ) ;
			note = note + chr;
		}
		else
		{
			mapping.insert( pair<string,int>( note , count ) );

			count++;
			note = "";
		}
		
	}

	unsigned int length = 0;
	unsigned int total_length = 0;
	for(int i=0; i<num_dic; i++ )
	{
		note = "";
		length = 0;
	
		for(int j = 0; j<strlen( (char*) dictionary[i] ); j++)
		{
			if( dictionary[i][j] != ',' )	
			{
				string chr( 1, dictionary[i][j] ) ;
				note = note + chr;
			}	
			else
			{
				length++;

				mapping.insert( pair<string,int>( note , count ) );
				count++;
				note = "";
			}
		}
		
		total_length = total_length + length;
		dictionary_array[i] = ( unsigned int * ) calloc( length , sizeof( unsigned int ) );
		dictionary_size[i] = length;
		
	}

	int pos = 0;
	note = "";

	for(int i=0; i<strlen( (char*) seq ); i++ )
	{		
		if( seq[i] != ',' )	
		{
			string chr( 1, seq[i] ) ;
			note = note + chr;
		}
		else
		{
			unordered_map<string, int>::const_iterator inside_map = mapping.find( note );
			seq_array[ pos ] = inside_map->second;
			note = "";
			pos++;
		}
	}



	for(int i=0; i<num_dic; i++ )
	{
		note = "";
		pos = 0;

		for(int j = 0; j<strlen( (char*) dictionary[i] ); j++)
		{

			if( dictionary[i][j] != ',' )	
			{
				string chr( 1, dictionary[i][j] ) ;
				note = note + chr;
			}
			else
			{
				unordered_map<string, int>::const_iterator inside_map = mapping.find( note );
				dictionary_array[ i ][ pos ] = inside_map->second;
				note = "";
				
				pos++;
			}

		}
	}

	*total_dictionary_length = total_length;

return 0;
}

