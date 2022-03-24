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

#ifndef __DEFS__
#define __DEFS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // memcpy
#include <math.h>       // pow, sqrt
#include <time.h>

#define SUCCESS         1
#define ERR_NOT_SQUARE -1
#define ERR_LINE_SUM   -2
#define ERR_ABSORBENT  -3

#define LIMIT   1024    // line size limit
#define MAXRUNS 10000   // number of runs
#define RESIDUE 1e-5    // residual difference between two iterations

/////// 1. randomgenerators.c
extern float exponential(float);
extern double nextuniform01();
extern double nextuniform(double a, double b);

////// 2. generic_functions.c
extern float** create_matrix(int);
extern void destroy_matrix(float**, int);
extern void init_matrix(float**, float, int);
extern void print_matrix(float**, int);
extern void print_array(float*, int);

////// 3. file_functions.c
extern int open_model(char*, float**);
extern int find_order(char*);

////// 4. markov.c (DTMC, CTMC), solution methods, etc.
extern int validate_mc(float**, int, int*, char type);
extern float** validate(char*, char, int*);

////// 5. dtmc.c
extern void solve_dtmc_power(float**, int);
extern void solve_dtmc_vmm(float**, int);
// simulation
extern void dtmc_simulator(float**, int, int, int*);
// power matrix
extern int converge_matrix(float**, int);
extern void multiply_matrix(float**, int);

// vmm
extern int converge_vector(float*, float*, int);
extern void multiply_vector(float*, float**, int);

////// 6. ctmc.c
extern void fix_ctmc(float**, int);
extern float** convert2dtmc(float**, int);
extern float discover_max(float**, int);
// simulation
float** convert2ctmc_prime(float**, int);
extern int ctmc_simulator(float**, int, float, int*);
extern int lowest_not_zero(float*, int, float*);


#endif
