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

/**
 * Returns the next exponential random variable according to a given rate (as parameter).
 * It converts a uniformly random variable to an exponential random variable.
 *   // from William Stewart's book (2009) 'Probability, Markov Chains,
 *   //   Queues, and Simulation: The Mathematical Basis of
 *   //   Performance Modeling'
 */
float exponential(float n) {
    float unif = (random()/(float)RAND_MAX); // this makes the number stay between 0 and 1
    return ((-1.0/n)*(log(1-unif))); // in C, the log functions returns the 
                                     // logarithm of x to the base of e  
}

/**
 * Returns the next uniform between 0 and 1.
 *
 */
double nextuniform01() {
   return (nextuniform(0, 1));
}

/**
 * Returns the next uniform between a and b.
 * If b >= a, then returns a number between 0 and 1.
 */
double nextuniform(double a, double b) {
   double unif = rand() / (double) RAND_MAX;
   if (a < b)
      unif = unif * (b - a) + a;
   return (unif);
}


