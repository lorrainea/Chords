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

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <float.h>
#include <sys/time.h>
#include <getopt.h>
#include <assert.h>
#include "chords.h"

static struct option long_options[] =
 {
   { "seqs-file",               required_argument, NULL, 'i' },
   { "output-file",             required_argument, NULL, 'o' },
   { "dictionary",            	required_argument, NULL, 'd' },
   { NULL,                      0,                 NULL,  0  }
 };


/* 
Decode the input switches 
*/
int decode_switches ( int argc, char * argv [], struct TSwitch * sw )
 {
   int          oi;
   int          opt;
   double       val;
   char       * ep;
   int          args;

   /* initialisation */
   sw -> input_filename                 = NULL;
   sw -> output_filename                = NULL;
   sw -> dictionary_filename            = NULL;
   args = 0;

   while ( ( opt = getopt_long ( argc, argv, "i:o:d:h", long_options, &oi ) ) != -1 ) 
    {

      switch ( opt )
       {
         case 'i':
           sw -> input_filename = ( char * ) malloc ( ( strlen ( optarg ) + 1 ) * sizeof ( char ) );
           strcpy ( sw -> input_filename, optarg );
           args ++;
           break;

         case 'o':
           sw -> output_filename = ( char * ) malloc ( ( strlen ( optarg ) + 1 ) * sizeof ( char ) );
           strcpy ( sw -> output_filename, optarg );
           args ++;
          break;

          case 'd':
           sw -> dictionary_filename = ( char * ) malloc ( ( strlen ( optarg ) + 1 ) * sizeof ( char ) );
           strcpy ( sw -> dictionary_filename, optarg );
           args ++;
          break;

          
         case 'h':
           return ( 0 );
       }
    }

   if ( args < 2 )
     {
       usage ();
       exit ( 1 );
     }
   else
     return ( optind );
 }

/* 
Usage of the tool 
*/
void usage ( void )
 {
   fprintf ( stdout, " Usage: chords <options>\n" );
   fprintf ( stdout, " Standard (Mandatory):\n" );
   fprintf ( stdout, "  -i, --input-file            <str>     Input filename.\n" );  
   fprintf ( stdout, "  -d, --dictionary-file       <str>     Dictionary filename.\n" );
  // fprintf ( stdout, "  -o, --output-file           <str>     Output filename.\n" );   
   
 }

double gettime( void )
{
    struct timeval ttime;
    gettimeofday( &ttime , 0 );
    return ttime.tv_sec + ttime.tv_usec * 0.000001;
}

