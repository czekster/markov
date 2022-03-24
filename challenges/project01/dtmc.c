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

void solve_dtmc_power(float** m, int size) {
   int runs = 0;
   // method
   do {
      multiply_matrix(m, size);
      if (++runs > MAXRUNS)
         break;
   } while (!converge_matrix(m, size));
   printf("Number of iterations: %d\n", runs-1);
   print_matrix(m, size);
}

void solve_dtmc_vmm(float** m, int size) {
   int runs = 0;
   float* pvec = (float*) malloc(sizeof(float) * size);
   float* old = (float*) malloc(sizeof(float) * size);
   // init vector
   pvec[0] = 1.0;  // initialise first position
   for (int i = 1; i < size; i++)
      pvec[i] = 0.0;
   // method
   do {
      memcpy(old, pvec, sizeof(float) * size); // copy to old array
      multiply_vector(pvec, m, size);
      if (++runs > MAXRUNS)
         break;
   } while (!converge_vector(old, pvec, size));
   printf("Number of iterations: %d\n", runs-1);
   for (int i = 0; i < size; i++)
      printf("%d=%f\n", i, pvec[i]);
   // free auxiliary vectors
   free(pvec);
   free(old);
}

int converge_matrix(float** m, int size) {
   int i, j;
   for (i = 0; i < size-1; i++) {
      for (j = 0; j < size; j++)
         if (sqrt(pow(m[i][j] - m[i+1][j], 2)) > RESIDUE)
            return 0;
   }
   return 1;
}

/** Performs a matrix-matrix product - this is a classic algorithm available in the Internet */
// based on https://www.programmingsimplified.com/c-program-multiply-matrices
void multiply_matrix(float** m, int size) {
   int c,d,k;
   float** aux = create_matrix(size);
   float tot = 0.0;
   for (c = 0; c < size; c++) {
      for (d = 0; d < size; d++) {
        for (k = 0; k < size; k++)
          tot += m[c][k] * m[k][d];
        aux[c][d] = tot;
        tot = 0.0;
      }
   }
   //memcpy(m, aux, sizeof(float) * size * size);
   for (c = 0; c < size; c++)
      for (d = 0; d < size; d++)
         m[c][d] = aux[c][d];
   destroy_matrix(aux, size);
}

//////////// functions for VMM ////////////////
/** Checks for convergence, i.e., all positions from two vectors must be greater than the RESIDUE constant. */
int converge_vector(float *r1, float *r2, int o) {
   int i;
   for (i = 0; i < o; i++)
      if (sqrt(pow(r1[i] - r2[i], 2)) > RESIDUE)
         return 0;
   return 1;
}


/** Performs a vector-matrix product. */
void multiply_vector(float *v, float **m, int o) {
   int i,j;
   float aux[o];
   for (i = 0; i < o; i++) {
      aux[i] = 0;
      for (j = 0; j < o; j++)
         aux[i] += m[j][i] * v[j];
   }
   memcpy(v, aux, sizeof(float) * o);
}

// DTMC simulator
void dtmc_simulator(float** m, int size, int samples, int* results) {
   float r;             // variable for saving random number
   int i;
   float acc;
   int state = 0; // initial state
   int runs = 0;
   srand(time(NULL));            // set initial random seed -- based on now
   for (i = 0; i < size; i++)   // states initialisation
      results[i] = 0;
   while (runs++ < samples) {
      r = (float) rand()/RAND_MAX;
      acc = 0.0;
      for (i = 0; i < size; i++) {
         acc += m[state][i];  // this accumulates the probabilities (similar to that idea of creating a new matrix with the accumulated values)
         if (r < acc) {
            results[i]++;
            state = i;
            break;
         }
      }
   }
}



