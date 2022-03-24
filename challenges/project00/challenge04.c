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
      printf("Usage: challenge04 <FILE> <OP>\n");
      exit(1);
   }
   char* filename = (char*)malloc(sizeof(char)*strlen(argv[1])+1);
   strcpy(filename, argv[1]);
   int op = atoi(argv[2]);
   if (op != 0 && op != 1) {
      printf("Usage: challenge04 <FILE> <OP>\n");
      printf("<OP> parameter must be 0 or 1.\nTry again.\n");
      exit(1);
   }
   printf("Working with file: %s\n", filename);

   int i;
   int runs = 0;
   int state = 0;
   int size = find_order(filename);

   float** m = create_matrix(size);
   float *pvec;
   float *old;

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

   switch (op) {
      case 0:
         // method
         do {
            multiply0(m, size);
            if (++runs > MAXRUNS)
               break;
         } while (!converge0(m, size));
         printf("Number of iterations: %d\n", runs-1);
         print_matrix(m, size);
      case 1: {
        pvec = (float*) malloc(sizeof(float) * size);
        old = (float*) malloc(sizeof(float) * size);
        // init vector
        pvec[0] = 1.0;  // initialise first position
        for (i = 1; i < size; i++)
           pvec[i] = 0.0;
        // method
        do {
           memcpy(old, pvec, sizeof(float) * size); // copy to old array
           multiply1(pvec, m, size);
           if (++runs > MAXRUNS)
              break;
        } while (!converge1(old, pvec, size));
        printf("Number of iterations: %d\n", runs-1);
        for (i = 0; i < size; i++)
           printf("%d=%f\n", i, pvec[i]);
        // free auxiliary vectors
        free(pvec);
        free(old);
      }
   }
   return EXIT_SUCCESS;
}

// input and output
/* OP = 0 (Power matrix method)
$ ./challenge04 markov.txt 0
Working with file: markov.txt
Success: that is one well-formed dtmc matrix.
Number of iterations: 3
0.041323 0.330577 0.628101 
0.041321 0.330585 0.628094 
0.041323 0.330575 0.628102 
Number of iterations: 5
0=0.041322
1=0.330578
2=0.628099
*/

/* OP = 1 (Vector-Matrix Multiplication method)
$ ./challenge04 markov.txt 1
Working with file: markov.txt
Success: that is one well-formed dtmc matrix.
Number of iterations: 15
0=0.041323
1=0.330577
2=0.628101
*/

