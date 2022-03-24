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
// Date: 23/03/2022

#include "defs.h"

float** create_matrix(int size) {
   float** m = (float **) malloc(sizeof(float*) * size);
   for (int i=0; i < size; i++) {
      m[i] = (float*) malloc(sizeof(float) * size);
   }
   return (m);
}

void destroy_matrix(float** m, int size) {
   // dealloc matrix and vectors
   for (int i = 0; i < size; i++)
      free(m[i]);
   free(m);
}

void init_matrix(float** m, float value, int size) {
   for (int i=0; i<size; i++)
      for (int j=0; j<size; j++)
         m[i][j] = value;
}

void print_matrix(float** m, int size) {
   for (int i=0; i<size; i++) {
      for (int j=0; j<size; j++) {
         printf("%f ", m[i][j]);
      }
      printf("\n");
   }
}

void print_array(float* a, int size) {
   for (int i=0; i<size; i++) {
      printf("%f\n", a[i]);
   }
}


