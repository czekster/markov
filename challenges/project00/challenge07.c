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
      printf("Usage: challenge07 <CTMC-MODEL> <TIME>\n");
      exit(1);
   }
   char* filename = (char*)malloc(sizeof(char)*strlen(argv[1])+1);
   strcpy(filename, argv[1]);
   float sim_time = atof(argv[2]);
   if (sim_time <= 0) {
      printf("Usage: challenge07 <CTMC-MODEL> <TIME>\n");
      printf("<TIME> parameter must be >0.\nTry again.\n");
      exit(1);
   }
   printf("Working with file: %s\n", filename);

   int state = 0;
   int size = find_order(filename);

   float** q = create_matrix(size);
   init_matrix(q, 0.0, size);
   int result = open_model(filename, q);
   switch (result) {
      case ERR_NOT_SQUARE:
         printf("Error: matrix is not square (lines != columns).\nTry again.\n");
         exit(1);
   }
   fix_ctmc(q, size);
   result = validate_ctmc(q, size, &state);
   printf("q matrix:\n");
   print_matrix(q, size);
   float** qprime = convert2ctmc_prime(q, size);
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

   int visits[size];
   int samples = ctmc_simulator(qprime, size, sim_time, visits);
   printf("qprime matrix:\n");
   print_matrix(qprime, size);
   printf("Simulator ran for %f units of time and %d samples.\n", sim_time, samples);
   for (int i = 0; i < size; i++)
      printf("%d=%f\n", i, (float)visits[i]/samples);

   destroy_matrix(q, size);
   destroy_matrix(qprime, size);
   return EXIT_SUCCESS;
}

// input and output
/*
$ ./challenge07 ctmc.txt 500000
Working with file: ctmc.txt
q matrix:
-16.000000 7.000000 9.000000 
1.000000 -11.000000 10.000000 
2.000000 3.000000 -5.000000 
Success: that is one well-formed ctmc matrix.
qprime matrix:
0.000000 7.000000 9.000000 
1.000000 5.000000 10.000000 
2.000000 3.000000 11.000000 
Simulator ran for 500000 samples.
0=0.098012
1=0.243420
2=0.658568
*/
