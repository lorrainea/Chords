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

int main(int argc, char **argv)
{
	struct TSwitch  sw;

	FILE *          in_fd;                  // the input file descriptor
	FILE *          dic_fd;                 // the dictionary file descriptor
	FILE *          out_fd;                 // the output file descriptor
        char *          input_filename;         // the input file name
	char *          dictionary_filename;        // the dictionary file name
        char *          output_filename;        // the output file name

        unsigned char * seq    = NULL;         // the sequence(s) in memory
        unsigned char * seq_id = NULL;         // the sequence(s) id in memory

	unsigned char ** dictionary    = NULL;         // the sequence(s) in memory
        unsigned char ** dictionary_id = NULL;         // the sequence(s) id in memory
	int i;

	/* Decodes the arguments */
        i = decode_switches ( argc, argv, &sw );

	/* Check the arguments */
        if ( i < 2 )
        {
                usage ();
                return ( 1 );
        }
        else
        {

                input_filename       = sw . input_filename;
		if ( input_filename == NULL )
		{
			fprintf ( stderr, " Error: Cannot open file for input!\n" );
			return ( 1 );
		}

		dictionary_filename       = sw . dictionary_filename;
		if ( dictionary_filename   == NULL )
		{
			fprintf ( stderr, " Error: Cannot open file for dictionary!\n" );
			return ( 1 );
		}
		output_filename         = sw . output_filename;

        }

	double start = gettime();

	if ( ! ( in_fd = fopen ( input_filename, "r") ) )
	{
		fprintf ( stderr, " Error: Cannot open file %s!\n", input_filename );
		return ( 1 );
	}

	if ( ! ( dic_fd = fopen ( dictionary_filename, "r") ) )
	{
		fprintf ( stderr, " Error: Cannot open file %s!\n", dictionary_filename );
		return ( 1 );
	}

	char c;
        unsigned int num_seqs = 0;          
	unsigned int max_alloc_seq_id = 0;
	unsigned int max_alloc_seq = 0;
	unsigned int seq_length = 1;

	do
        {
         	 if ( num_seqs >= max_alloc_seq_id )
                 {
                 	seq_id = ( unsigned char * ) realloc ( seq_id,   ( max_alloc_seq_id + ALLOC_SIZE ) * sizeof ( unsigned char * ) );
                        max_alloc_seq_id += ALLOC_SIZE;
                 }

                 unsigned int max_alloc_seq_id_len = 0;
                 unsigned int seq_id_len = 0;

                 seq_id = NULL;

                 while ( ( c = fgetc( in_fd ) ) != '\n' )
                 {
			if ( seq_id_len >= max_alloc_seq_id_len )
			{
				seq_id = ( unsigned char * ) realloc ( seq_id,   ( max_alloc_seq_id_len + ALLOC_SIZE ) * sizeof ( unsigned char ) );
				max_alloc_seq_id_len += ALLOC_SIZE;
			}

			
			seq_id[ seq_id_len++ ] = c;
		}
 		seq_id[ seq_id_len ] = '\0';

                
		if ( num_seqs >= max_alloc_seq )
                {
                        seq = ( unsigned char * ) realloc ( seq,   ( max_alloc_seq + ALLOC_SIZE ) * sizeof ( unsigned char ) );
                        max_alloc_seq += ALLOC_SIZE;
                }

                unsigned int seq_len = 0;
                unsigned int max_alloc_seq_len = 0;

                seq = NULL;

		c = fgetc( in_fd );
		c = fgetc( in_fd );

                while ( ( c = fgetc( in_fd ) ) != EOF && c != ']' )
                {
                        if( seq_len == 0 && c == '\n' )
                        {
                                fprintf ( stderr, " Omitting empty sequence in file %s!\n", input_filename );
                                c = fgetc( in_fd );
                                break;
                        }
                        if( c == '\n' || c == ' ' || c == ')' ||  c == '#' ) continue;

                        c = toupper( c );

			if( c == '(' )
			{
				c = ',';
				seq_length++;	
			}

                        if ( seq_len >= max_alloc_seq_len )
                        {
                                seq = ( unsigned char * ) realloc ( seq,   ( max_alloc_seq_len + ALLOC_SIZE ) * sizeof ( unsigned char ) );
                                max_alloc_seq_len += ALLOC_SIZE;
                        }
                        seq[ seq_len++ ] = c;

                }

                if( seq_len != 0 )
                {
                        if ( seq_len >= max_alloc_seq_len )
                        {
                                seq = ( unsigned char * ) realloc ( seq,   ( max_alloc_seq_len + ALLOC_SIZE ) * sizeof ( unsigned char ) );
                                max_alloc_seq_len += ALLOC_SIZE;
                        }
                        seq[ seq_len++ ] = ',';
			seq[ seq_len ] = '\0';
                        num_seqs++;
                }

        } while( c != ']' );

	char d;
        unsigned int num_dic = 0;          
	unsigned int max_alloc_dic_id = 0;
	unsigned int max_alloc_dic = 0;
	unsigned int total_length = 0;

	do
	{
		
		if ( num_dic >= max_alloc_dic_id )
		{
			dictionary_id = ( unsigned char ** ) realloc ( dictionary_id,   ( max_alloc_dic_id + ALLOC_SIZE ) * sizeof ( unsigned char * ) );
			max_alloc_dic_id += ALLOC_SIZE;
		}

		unsigned int max_alloc_dic_id_len = 0;
		unsigned int dic_id_len = 0;

		dictionary_id[ num_dic ] = NULL;

                while ( ( d = fgetc( dic_fd ) ) != EOF && d != '[' )
                {
                	if ( dic_id_len >= max_alloc_dic_id_len )
                        {
                        	dictionary_id[ num_dic ] = ( unsigned char * ) realloc ( dictionary_id[ num_dic ],   ( max_alloc_dic_id_len + ALLOC_SIZE ) * sizeof ( unsigned char ) );
                                max_alloc_dic_id_len += ALLOC_SIZE;
                        }

			if( d == '\n' ) 
				continue;

                       	dictionary_id[ num_dic ][ dic_id_len++ ] = d;
                }
                dictionary_id[ num_dic ][ dic_id_len ] = '\0';


		if ( num_dic >= max_alloc_dic )
		{
			dictionary = ( unsigned char ** ) realloc ( dictionary,   ( max_alloc_dic + ALLOC_SIZE ) * sizeof ( unsigned char * ) );
			max_alloc_dic += ALLOC_SIZE;
		}

		unsigned int dic_len = 0;
		unsigned int max_alloc_dic_len = 0;

		dictionary[ num_dic ] = NULL;

		d = fgetc( dic_fd );

		while ( ( d = fgetc( dic_fd ) ) != EOF && d != ']' )
		{
			if( dic_len == 0 && d == '\n' )
			{
				fprintf ( stderr, " Omitting empty sequence in file %s!\n", dictionary_filename );
				d = fgetc( dic_fd );
				break;
			}
			if( d == '\n' || d == ' '  || d == ')' || d == '#' ) 
				continue;

			d = toupper( d );
	
			if( d == '(' )
				d = ',';

			if ( dic_len >= max_alloc_dic_len )
			{
				dictionary[ num_dic ] = ( unsigned char * ) realloc ( dictionary[ num_dic ],   ( max_alloc_dic_len + ALLOC_SIZE ) * sizeof ( unsigned char ) );
				max_alloc_dic_len += ALLOC_SIZE;
			}
			dictionary[ num_dic ][ dic_len++ ] = d;
		}

		if( dic_len != 0 )
		{
			if ( dic_len >= max_alloc_dic_len )
			{
				dictionary[ num_dic ] = ( unsigned char * ) realloc ( dictionary[ num_dic ],   ( max_alloc_dic_len + ALLOC_SIZE ) * sizeof ( unsigned char ) ); 
				max_alloc_dic_len += ALLOC_SIZE;
			}
			dictionary[ num_dic ][ dic_len++ ] = ',';
 			dictionary[ num_dic ][ dic_len ] = '\0';

                        num_seqs++;


			total_length += dic_len;
			num_dic++;
		}
		
	} while( d != EOF );


	if ( fclose ( dic_fd ) )
	{
		fprintf( stderr, " Error: file close error!\n");
		return ( 1 );
	}


	unsigned int ** dictionary_array = ( unsigned int ** ) calloc( ( num_dic  ) , sizeof( unsigned int * ) );
	unsigned int * seq_array = ( unsigned int * ) calloc( ( seq_length ) , sizeof( unsigned int ) );
	
	unsigned int total_dictionary_length = 0;
	
	unsigned int * dictionary_size = ( unsigned int * ) calloc ( num_dic, sizeof( unsigned int ) );

	unordered_map<string, int> mapping;
	create_int_seqs( dictionary, seq, dictionary_array, seq_array, mapping, num_dic, dictionary_size, &total_dictionary_length );

	for ( int i = 0; i < num_dic; i ++ )
	{
		free ( dictionary[i] );
	}	
	free ( seq );
	free ( dictionary );

	//fprintf ( stderr, " Preparing the output\n" );

	/*if ( ! ( out_fd = fopen ( output_filename, "w") ) )
	{
		fprintf ( stderr, " Error: Cannot open file %s!\n", output_filename );
		return ( 1 );
	}*/

	Chords * factors = ( Chords * ) calloc ( seq_length, sizeof( Chords ) );
	
	suffix_tree( dictionary_array, seq_array, factors, seq_length, num_dic, dictionary_size, &total_dictionary_length );


	vector<pair<int,int>> * pairs = new vector<pair<int,int>>;

	split( factors, seq_length, pairs );

	for(int i=0; i<seq_length; i++)
		cout<<factors[i].length<<" ";


	//if( pairs->size() == 0 )
		//cout<<"no breakdown"<<endl;
	cout<<endl;
	for(int i=0; i<pairs->size(); i++)
		cout<<"("<<pairs->at(i).first<<" -- "<<pairs->at(i).second<<")"<<endl;
		
	/*if ( fclose ( out_fd ) )
	{
		fprintf( stderr, " Error: file close error!\n");
		return ( 1 );
	}*/

	double end = gettime();

        fprintf( stderr, "Elapsed time: %lf secs.\n", end - start );

	for ( int i = 0; i < num_dic; i ++ )
	{
		free( dictionary_id[i] );
	}	
	free ( seq_id );
	free ( dictionary_id );
        free ( sw . input_filename );
        free ( sw . output_filename );
        free ( sw . dictionary_filename );

return ( 0 );
}
