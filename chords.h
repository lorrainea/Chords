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

#define INITIAL_SC		-100000
#define ALLOC_SIZE               104857

#include <unordered_map>
#include <vector>

using namespace std;

struct TSwitch
 {
   char * input_filename;
   char * output_filename;
   char * dictionary_filename;
 };

struct Chords
 {
   unsigned int	length;
   unsigned int index;
   unsigned int pos;
 };


double gettime( void );

int decode_switches ( int argc, char * argv [], struct TSwitch * sw );

unsigned int create_int_seqs( unsigned char ** dictionary, unsigned char * seq, unsigned int ** dictionary_array, unsigned int * seq_array, unordered_map<string, int> mapping, unsigned int num_dic, unsigned int * dictionary_size, unsigned int * total_dictionary_length );

unsigned int suffix_tree( unsigned int ** dictionary_array, unsigned int * seq_array, Chords * factors, unsigned int seq_len, unsigned int num_dic, unsigned int * dictionary_size, unsigned int * total_dictionary_length );

unsigned int split( Chords * factors, unsigned int seq_length, vector<pair<int,int>> * pairs );

void usage ( void );
