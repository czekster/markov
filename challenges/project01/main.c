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

// Author: Ricardo M. Czekster (rczekster@gmail.com)
// Supporting files: https://github.com/czekster/markov
// Date: 23/03/2022

#include "defs.h"

void echo_help() {
   printf("This is the Markov chain solver [last update: 23/03/2022].\n");
   printf("To run DTMC: markov <FILE> <OP>\n");
   printf(" where <OP> is one out of these options:\n");
   printf("   0 Solve DTMC - Power Matrix\n");
   printf("   1 Solve DTMC - Vector-Matrix Multiplication\n");
   printf("   2 Simulate DTMC (pass <SAMPLES> parameter!)\n");
   printf("   3 Convert CTMC to Embedded DTMC\n");
   printf("   4 Simulate CTMC (pass <TIME> parameter!)\n");
}

/**
 *  Main file.
 */
int main(int argc, char *argv[]) {
   char* filename;
   int op;
   if (argc <= 2) {
      echo_help();
      exit(1);
   } else {
      filename = (char*)malloc(sizeof(char)*strlen(argv[1])+1);
      strcpy(filename, argv[1]);
      op = atoi(argv[2]);
      if (op < 0 || op > 4) {
         printf("Invalid <OP> parameter.\nTry again.\n");
         echo_help();
         exit(1);
      }
      printf("Processing file '%s' for OP=%d\n", filename, op);
      float** mat; // matrix to work
      int size;    // size of matrix
      if (op == 0 || op == 1 || op == 2)
         mat = validate(filename, 'd', &size);    // dtmc - method will return matrix and change size
      else mat = validate(filename, 'c', &size);  // ctmc - idem
      switch(op) {
         case 0: {
            printf("Performing Power method.\n");
            solve_dtmc_power(mat, size);
         }
            break;
         case 1: {
            printf("Performing VMM method.\n");
            solve_dtmc_vmm(mat, size);
         }
            break;
         case 2: {
            printf("Performing DTMC simulation method.\n");
            char input[10];
            int samples;
            do {
               printf("Inform number of <SAMPLES>: ");
               fgets(input, 10, stdin);
               samples = atoi(input);
               if (samples <= 0 || samples > 500000) {
                  printf("<SAMPLES> parameter must be between (0; 500,000)\nTry again.\n");
               }
            } while (samples <= 0 || samples > 500000);
            int visits[size];
            dtmc_simulator(mat, size, samples, visits);
            printf("Simulator ran for %d samples.\n", samples);
            for (int i = 0; i < size; i++)
               printf("%d=%f\n", i, (float)visits[i]/samples);
            break;
         }
         case 3: {
            printf("Converting CTMC to embedded DTMC.\n");
            fix_ctmc(mat, size);   // destroy main diagonal and replace with negative sum of line (except diagonal)
            float** m = convert2dtmc(mat, size);
            printf("CTMC:\n");
            print_matrix(mat, size);
            printf("(embedded) DTMC:\n");
            print_matrix(m, size);
            destroy_matrix(m, size);
            break;
         }
         case 4: {
            printf("Performing CTMC simulation method.\n");
            char input[10];
            float sim_time;
            do {
               printf("Inform <TIME>: ");
               fgets(input, 10, stdin);
               sim_time = atof(input);
               if (sim_time <= 0 || sim_time > 999999) {
                  printf("<TIME> parameter must be between (0; 999,999)\nTry again.\n");
               }
            } while (sim_time <= 0 || sim_time > 500000);
            fix_ctmc(mat, size);
            printf("q matrix:\n");
            print_matrix(mat, size);
            float** qprime = convert2ctmc_prime(mat, size);
            int visits[size];
            int samples = ctmc_simulator(qprime, size, sim_time, visits);
            printf("qprime matrix:\n");
            print_matrix(qprime, size);
            printf("Simulator ran for %f units of time and %d samples.\n", sim_time, samples);
            for (int i = 0; i < size; i++)
               printf("%d=%f\n", i, (float)visits[i]/samples);
            destroy_matrix(qprime, size);
            break;
         }
      }
      destroy_matrix(mat, size);
      free(filename);
   }
   return EXIT_SUCCESS;
}


