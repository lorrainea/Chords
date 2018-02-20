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


	int i = 0;

	for(int i=0; i<seq_length; i++)
	{
		if( factors[i].length == 0 )
		return 0;
	}

	while( i < seq_length )
	{
		pairs->push_back( pair<int,int>( i+1, i+factors[i].length ) );

		i = i + factors[i].length;
	}
 
return 0;
}
