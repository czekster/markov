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
   if (argc != 3) {
      printf("Usage: challenge05 <FILE> <SAMPLES>\n");
      exit(1);
   }
   char* filename = (char*)malloc(sizeof(char)*strlen(argv[1])+1);
   strcpy(filename, argv[1]);
   int samples = atoi(argv[2]);
   if (samples <= 0 || samples > 500000) {
      printf("Usage: challenge05 <FILE> <SAMPLES>\n");
      printf("<SAMPLES> parameter must be >0 and <500000.\nTry again.\n");
      exit(1);
   }
   printf("Working with file: %s\n", filename);

   int state = 0;
   int size = find_order(filename);

   float** m = create_matrix(size);

   init_matrix(m, 0.0, size);
   int result = open_model(filename, m);
   switch (result) {
      case ERR_NOT_SQUARE:
         printf("Error: matrix is not square (lines != columns).\nTry again.\n");
         exit(1);
   }
   result = validate_dtmc(m, size, &state); 
   switch (result) {
      case ERR_LINE_SUM:
         printf("Error: line does NOT sum 1.0.\nTry again.\n");
         exit(1);
      case ERR_ABSORBENT:
         printf("Error: chain with absorbent state (state=%d).\nTry again.\n", state);
         exit(1);
      case SUCCESS:
         printf("Success: that is one well-formed dtmc matrix.\n");
         break;
   }

   int visits[size];
   dtmc_simulator(m, size, samples, visits);
   printf("Simulator ran for %d samples.\n", samples);
   for (int i = 0; i < size; i++)
      printf("%d=%f\n", i, (float)visits[i]/samples);

   destroy_matrix(m, size);
   return EXIT_SUCCESS;
}

// input and output
/*
$ ./challenge05 markov.txt 10000
Working with file: markov.txt
Success: that is one well-formed dtmc matrix.
Simulator ran for 10000 samples.
0=0.041500
1=0.331600
2=0.626900
*/

