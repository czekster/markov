/*
This is a file to be used with the book "Markov Chains for programmers".
Copyright (C) 2022-  Ricardo M. Czekster

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

// Author: Ricardo M. Czekster (rczekster@gmail.com)
// Date: 14/03/2022

// Compile with: gcc -o challenge03 challenge03.c
// Execute with: ./challenge03
//    

#include "defs.h"

// main function
int main(int argc, char *argv[]) {
   if (argc != 1) {
      printf("Usage: challenge03\n");
      exit(1);
   }

   float matrix[LIN][COL] = {
      { 0.1, 0.9, 0.0 },
      { 0.0, 0.0, 1.0 },
      { 0.1, 0.0, 0.9 }
   };

   print_static_dtmc(matrix);
   int state = 0;
   int result = validate_static_dtmc(matrix, &state);
   switch (result) {
      case ERR_LINE_SUM:
         printf("Error: line does NOT sum 1.0.\nTry again.\n");
         break;
      case ERR_NOT_SQUARE:
         printf("Error: matrix is not square (lines != columns).\nTry again.\n");
         break;
      case ERR_ABSORBENT:
         printf("Error: chain with absorbent state (state=%d).\nTry again.\n", state);
         break;
      case SUCCESS:
         printf("Success: that is one well-formed dtmc matrix.\n");
         break;
   }
   return EXIT_SUCCESS;
}

// input and output

/*
$ ./challenge03
$ ./challenge03
0.100000 0.900000 0.000000 
0.000000 0.000000 1.000000 
0.100000 0.000000 0.900000 
Success: that is one well-formed dtmc matrix.
*/

