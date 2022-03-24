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

// use the Makefile (make clean && make) from the command-line
// you may also compile specific challenges, e.g., make challenge04
// Implementations in "markov.c" file

#ifndef __DEFS__
#define __DEFS__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>     // memcpy
#include <math.h>       // pow, sqrt

#define LIN  3
#define COL  3
#define SIZE 3

#define SUCCESS         1
#define ERR_NOT_SQUARE -1
#define ERR_LINE_SUM   -2
#define ERR_ABSORBENT  -3

#define LIMIT   1024    // line size limit
#define MAXRUNS 10000   // number of runs
#define RESIDUE 1e-5    // residual difference between two iterations

// prototypes //

extern int validate_dtmc(float**, int, int*);
extern void print_matrix(float**, int);
extern void print_array(float*, int);

// working with files/models
extern int open_model(char*, float**);
extern int find_order(char*);

// matrix related
extern float** create_matrix(int);
extern void destroy_matrix(float**, int);
extern void init_matrix(float**, float, int);

// challenge03
extern int validate_static_dtmc(float m[LIN][COL], int*);
extern void print_static_dtmc(float m[LIN][COL]);
extern void print_static_array(float a[SIZE]);

// challenge04
//    power matrix
extern int converge0(float**, int);
extern void multiply0(float**, int);

//    vmm
extern int converge1(float*, float*, int);
extern void multiply1(float*, float**, int);

// challenge05
extern void dtmc_simulator(float**, int, int, int*);

// challenge06
extern int validate_ctmc(float**, int, int*);
extern void fix_ctmc(float**, int);
extern float** convert2dtmc(float**, int);
extern float discover_max(float**, int);

// challenge07
extern float** convert2ctmc_prime(float** q, int size);
extern float exponential(float);
extern int ctmc_simulator(float**, int, float, int*);
extern int lowest_not_zero(float*, int, float*);


#endif

