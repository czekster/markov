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

/*Destroys 'original' diagonal and replace it with the sum of the line times -1*/
void fix_ctmc(float** q, int size) {
   float acc;
   for (int i=0; i<size; i++) {
      acc = 0.0;
      for (int j=0; j<size; j++) {
         if (i != j) // except diagonal
            acc += q[i][j];
      }
      q[i][i] = acc * (-1);
   }
}

float** convert2dtmc(float** q, int size) {
   float** d;
   d = create_matrix(size);

   float max = discover_max(q, size);
   for (int i=0; i<size; i++) {
      for (int j=0; j<size; j++) {
            d[i][j] = (i==j?1:0) - q[i][j]/max;
      }
   }
   return d;
}

float discover_max(float** q, int size) {
   float max=0.0;
   for (int i=0; i<size; i++) {
      for (int j=i; j<size; j++) {
         if (i == j && abs(q[i][j]) > max) {
            max = abs(q[i][j]);
         }
      }
   }
   return (max*-1);
}

/// simulation of CTMC

float** convert2ctmc_prime(float** q, int size) {
   float** qprime;
   qprime = create_matrix(size);
   float max = discover_max(q, size);
   for (int i=0; i<size; i++) {
      for (int j=0; j<size; j++) {
         qprime[i][j] = q[i][j] - (max * (i==j?1:0));
      }
   }
   return qprime;
}

/*This function will select the next state: the lowest value drawn from exponential distr. other than zero.*/
int lowest_not_zero(float* qline, int size, float* curr_time) {
   float r;
   float lowest = RAND_MAX; // set the lowest to a large number
   int nextstate = 0;
   for (int i = 0; i < size; i++) {
      r = exponential(qline[i]);
      if (r < lowest && r != 0.0) {
         lowest = r;
         nextstate = i;
         *curr_time += r;     // updates time
      }
   }
   return nextstate;
}

int ctmc_simulator(float** qprime, int size, float sim_time, int* results) {
   int i, runs = 0;
   int state = 0;        // initial state
   int nextstate = 0;    // next state to visit
   float curr_time = 0;
   srand(time(NULL));            // set initial random seed -- based on now
   for (i = 0; i < size; i++)    // states initialisation
      results[i] = 0;
   while (curr_time < sim_time) {
      nextstate = lowest_not_zero(qprime[state], size, &curr_time); // the idea here is that the 'fastest' transition 'wins' the 'race' ;)
      results[nextstate]++;
      //printf("\tcurrent state: %d next state: %d\n", state, nextstate);
      state = nextstate;
      runs++;
   }
   return runs;
}


