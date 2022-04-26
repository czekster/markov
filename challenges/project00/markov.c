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
// Date: 24/03/2022

// implementations

#include "defs.h"

// traverse file (first line) and return a 'tentative' order (it will have to pass other tests later)
int find_order(char* file) {
   int j=0;
   int orderj=0;
   FILE *fp;
   char line[LIMIT];
   char *pch;
   fp = fopen(file, "r");
   if (fp == NULL) {
      printf("Error while opening file.\n");
      exit(1);
   }
   while (fgets( line, LIMIT, fp) != NULL ) {
      line[strcspn(line, "\n")] = 0;  // remove \n from line
      if (line[0] == '#')             // bypass comments
          continue;
      pch = strtok(line," ");
      do {
         j++;
         pch = strtok(NULL, " ");
      } while (pch != NULL);
      orderj = j;
      break;
   }
   fclose(fp);
   return orderj;
}

int open_model(char* file, float **m) {
   int i=0, j=0;
   int orderj=0;
   FILE *fp;
   char line[LIMIT];
   char *pch;
   fp = fopen(file, "r");
   if (fp == NULL) {
      printf("Error while opening file.\n");
      exit(1);
   }

   while (fgets( line, LIMIT, fp) != NULL ) {
      if (line[0]=='\n') continue;
      line[strcspn(line, "\n")] = 0;  // remove \n from line
      if (line[0] == '#')             // bypass comments
          continue;
      pch = strtok(line," ");
      do {
         m[i][j] = atof(pch);
         j++;
         pch = strtok(NULL, " ");
      } while (pch != NULL);
      i++;
      orderj = j;
      j = 0;
   }
   if (i != orderj) {
      return ERR_NOT_SQUARE;
   }
   fclose(fp);
   return SUCCESS;
}

int validate_dtmc(float** m, int size, int* state) {
   for (int i=0; i<size; i++) {
      int incoming = 0;
      int outgoing = 0;
      float line_sum = 0.0;
      *state = i;

      for (int j=0; j<size; j++) {
         line_sum += m[i][j];
         if (m[i][j] != 0.0)
            outgoing++;
         if (m[j][i] != 0.0)
            incoming++;
      }
      //printf("i=%d in=%d out=%d\n", i, incoming, outgoing);
      if (line_sum < 0.99 && line_sum > 1.01)
         return ERR_LINE_SUM;
      else
      if ((outgoing == 1 && m[i][i] > 0) || (incoming == 1 && outgoing == 0))
         return ERR_ABSORBING;
   }
   return SUCCESS;
}

int validate_static_dtmc(float m[LIN][COL], int* state) {
   if (LIN != COL)
      return ERR_NOT_SQUARE;
   for (int i=0; i<LIN; i++) {
      int incoming = 0;
      int outgoing = 0;
      float line_sum = 0.0;
      *state = i;

      for (int j=0; j<COL; j++) {
         line_sum += m[i][j];
         if (m[i][j] != 0.0)
            outgoing++;
         if (m[j][i] != 0.0)
            incoming++;
      }
      //printf("i=%d in=%d out=%d\n", i, incoming, outgoing);
      if (line_sum < 0.99999 && line_sum > 1.00001)
         return ERR_LINE_SUM;
      else
      if ((outgoing == 1 && m[i][i] > 0) || (incoming == 1 && outgoing == 0))
         return ERR_ABSORBING;
   }
   return SUCCESS;
}

void print_static_dtmc(float m[LIN][COL]) {
   for (int i=0; i<LIN; i++) {
      for (int j=0; j<COL; j++) {
         printf("%f ", m[i][j]);
      }
      printf("\n");
   }
}

void print_static_array(float a[SIZE]) {
   for (int i=0; i<LIN; i++) {
      printf("%f\n", a[i]);
   }
}

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

//////////// functions for Power Matrix ////////////////

/** Checks for convergence, i.e., all positions from two vectors must be greater than the RESIDUE constant. */
int converge0(float** m, int size) {
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
void multiply0(float** m, int size) {
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
int converge1(float *r1, float *r2, int o) {
   int i;
   for (i = 0; i < o; i++)
      if (sqrt(pow(r1[i] - r2[i], 2)) > RESIDUE)
         return 0;
   return 1;
}


/** Performs a vector-matrix product. */
void multiply1(float *v, float **m, int o) {
   int i,j;
   float aux[o];
   for (i = 0; i < o; i++) {
      aux[i] = 0;
      for (j = 0; j < o; j++)
         aux[i] += m[j][i] * v[j];
   }
   memcpy(v, aux, sizeof(float) * o);
}

// challenge 05
// implementations

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

// challenge 06
int validate_ctmc(float** q, int size, int* state) {
   for (int i=0; i<size; i++) {
      int incoming = 0;
      int outgoing = 0;
      float line_sum = 0.0;
      *state = i;

      for (int j=0; j<size; j++) {
         line_sum += q[i][j];
         if (q[i][j] != 0.0)
            outgoing++;
         if (q[j][i] != 0.0)
            incoming++;
      }
      //printf("i=%d in=%d out=%d\n", i, incoming, outgoing);
      if (line_sum != 0.0)
         return ERR_LINE_SUM;
      else
      if (incoming == 0 || (outgoing == 1 && q[i][i] > 0.0))
         return ERR_ABSORBING;
   }
   return SUCCESS;
}

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

// challenge 07

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

float exponential(float n) {
    float unif = (random()/(float)RAND_MAX); // this makes the number stay between 0 and 1
    return ((-1.0/n)*(log(1-unif))); // in C, the log functions returns the 
                                     // logarithm of x to the base of e  
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


