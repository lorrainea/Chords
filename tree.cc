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
#include <sdsl/suffix_trees.hpp>
#include <sdsl/util.hpp>
#include <sdsl/cst_sct3.hpp>
#include <sdsl/int_vector.hpp>
#include <sdsl/sdsl_concepts.hpp>
#include "chords.h"

using namespace sdsl;
using namespace std;
typedef cst_sct3<> cst_t;
typedef cst_sada<> csts_t;
typedef bp_interval<> Node;

cst_sct3<csa_wt_int<wt_int<rrr_vector<>>>> cst;

unsigned int suffix_tree( unsigned int  ** dictionary_array, unsigned int * seq_array, Chords * factors, unsigned int seq_len, unsigned int num_dic, unsigned int * dictionary_size, unsigned int * total_dictionary_length )
{
	int_vector<> total_dic_array( *total_dictionary_length + num_dic - 1 );


	
	int count = 0;
	for(int i=0; i<num_dic; i++)
	{

		for( int j=0; j<dictionary_size[i]; j++)
		{
			total_dic_array[count] = dictionary_array[i][j];
			count++;
		}

		if( i < num_dic-1 )
			total_dic_array[count] = 1;

		count++;	
	}

	construct_im( cst, total_dic_array );

	Node current = cst.root();


	unsigned int i = 0;	
	unsigned int k = i ;
	unsigned int start = k;
	unsigned int match = 0;
	bool complete = false;
	bool matches = false;


	while( i < seq_len )
	{
		start = k;
		complete = false;
		matches = false;

		if( cst.child( current, seq_array[k] ) != cst.root() )
		{
			for(int j = match; j<cst.depth( cst.child( current, seq_array[start] ) ); j++ )
			{
				if( cst.edge( cst.child( current, seq_array[start] ), j+1 ) == seq_array[k] )
				{
					match++;
					k++;

					matches = true;

					if( k >= seq_len )
					{
						factors[i].length = seq_len - i;
						i++;
						complete = true;

						break;

					}
				}
				else
				{
					factors[i].length = k - i;
					i++;
					matches = false;
			
					break;
				}
			}
					
			if( complete == false && matches == true )
			{
				start = k;
				current = cst.child( current, seq_array[k-1] );
			}
			else if( complete == true || matches == false )
			{
				k = i;
				start = k;
				current = cst.sl( cst.parent(current) );
				match = cst.depth(  cst.parent(current) );
			}
		}
		else
		{
			factors[i].length = k - i ;
			i++;
			k = i;
			current = cst.sl(cst.parent( cst.parent(current) ));
			match = cst.depth( current );
		}

	}

return 0;
}
