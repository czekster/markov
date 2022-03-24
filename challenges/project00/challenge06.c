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

#include "defs.h"

// main function
int main(int argc, char *argv[]) {
   if (argc != 2) {
      printf("Usage: challenge06 <FILE>\n");
      exit(1);
   }
   char* filename = (char*)malloc(sizeof(char)*strlen(argv[1])+1);
   strcpy(filename, argv[1]);
   printf("Working with file: %s\n", filename);

   int size = find_order(filename);

   float** q = create_matrix(size);

   init_matrix(q, 0.0, size);
   int result = open_model(filename, q);
   switch (result) {
      case ERR_NOT_SQUARE:
         printf("Error: matrix is not square (lines != columns).\nTry again.\n");
         exit(1);
   }
   int state = 0;
   fix_ctmc(q, size);   // destroy main diagonal and replace with negative sum of line (except diagonal)
   float max = discover_max(q, size);
   printf("max=%f\n", max);
   float** m = convert2dtmc(q, size);

   result = validate_ctmc(q, size, &state);
   switch (result) {
      case ERR_LINE_SUM:
         printf("Error: line does NOT sum 0.0.\nTry again.\n");
         exit(1);
      case ERR_ABSORBENT:
         printf("Error: chain with absorbent state (state=%d).\nTry again.\n", state);
         exit(1);
      case SUCCESS:
         printf("Success: that is one well-formed ctmc matrix.\n");
         break;
   }

   printf("CTMC:\n");
   print_matrix(q, size);
   printf("DTMC\n");
   print_matrix(m, size);

   // deallocation
   destroy_matrix(q, size);
   destroy_matrix(m, size);

   return EXIT_SUCCESS;
}

// input and output
/*
$ ./challenge06 ctmc.txt 
Working with file: ctmc.txt
max=-27.000000
Success: that is one well-formed ctmc matrix.
CTMC:
-9.000000 2.000000 3.000000 4.000000 
5.000000 -13.000000 3.000000 5.000000 
9.000000 9.000000 -27.000000 9.000000 
1.000000 0.000000 2.000000 -3.000000 
DTMC
0.666667 0.074074 0.111111 0.148148 
0.185185 0.518519 0.111111 0.185185 
0.333333 0.333333 0.000000 0.333333 
0.037037 0.000000 0.074074 0.888889 
*/

