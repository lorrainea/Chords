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
#include <fstream>
#include <float.h>
#include "chords.h"

using namespace std;


unsigned int split( Chords * factors, unsigned int seq_length, vector<pair<int,int>> * pairs )
{

	int * V = ( int * ) calloc ( seq_length+1, sizeof( int ) );
	multimap<int,int> * E = new multimap<int,int> ;

	int i = 0;


	int * dist = ( int * ) calloc ( seq_length+1, sizeof( int ) );

	for(int i = 0; i<=seq_length; i++)
		dist[i] = seq_length+1;

	int * prev = ( int * ) calloc ( seq_length+1, sizeof( int ) );

	dist[0] = 0;
	
	for(int i=0; i<=seq_length; i++)
	{
		E->insert(pair<int,int>(i,i+factors[i].length));
		E->insert(pair<int,int>(i,i+1));

		
	}

	for(unsigned int a =0; a<=seq_length; a++ )
	{
		for(unsigned int b = 0; b<a;b++ )
		{
			pair<int,int> edge(a,b);
			multimap<int,int>::const_iterator found = E->find ( b );


  			if ( found != E->end() && found->second == a )
			{

				if( dist[b] + 1 <dist[a] )
				{		
					dist[a] = dist[b] +1;
					prev[a] = b;
				}



			}
			
		}
	}

	int l = seq_length;
	while( l  > 0 )
	{
		unsigned int second = l;
		unsigned int first = prev[l];
		l = first;
		pairs->insert( pairs->begin(), pair<int,int>( first, second ) );
	}

	free( V );
	free( E );
	free( dist );
	free( prev );
 
return 0;
}
