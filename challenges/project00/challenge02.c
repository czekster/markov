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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> // for the log function; compile with -lm

// Author: Ricardo M. Czekster (rczekster@gmail.com)
// Date: 11/03/2022

// Compile with: gcc -o challenge01 challenge01.c -lm
// Execute with: ./challenge02 20 10
//    (this will generate 10 samples from the exponential
//     for parameter equal to 20)

// prototypes
extern float exponential(float);
void showN_exponential(float,int);

// main function
int main(int argc, char *argv[]) {

   srand(time(NULL)); // init seed (using current time - this will produce different numbers every time)
   if (argc != 3) {
      printf("Usage: challenge02 <N> <M>\n \
              where N is the PARAMETER for\n \
              the exponential function and\n \
              M is the number of samples.\n");
      exit(1);
   }
   float n = atof(argv[1]); // converts the parameter
   int m = atoi(argv[2]);
   printf("Computing for N=%f and M=%d to sample the exponential distribution...\n", n, m);

   showN_exponential(n, m);

   return EXIT_SUCCESS;
}

// implementations

void showN_exponential(float n, int m) {
   for (int i=0; i < m; i++) {
      float exp_number = exponential(n);
      printf("%9f ", exp_number);
      if ((i+1) % 10 == 0)
         printf("\n"); // print 10 numbers then add a \n
   }
}

// input and output

/*
$ ./challenge02 20 100
Computing for N=20.000000 and M=100 to sample the exponential distribution...
 1.641338 56.194500 26.180708  6.613407  3.943066 19.365234 30.872002  1.662569  6.691887  9.295306 
24.420124 10.179952  4.425062 16.420073  2.477910 18.279993  0.263449  7.071873  2.592846  4.237203 
16.175041 33.646179 11.985269 11.495975 13.414392  5.261867  5.276452  2.540730  3.637642  3.943299 
21.134207  5.623135  2.527672  9.635766 14.958322  7.066710  0.051658  7.509507  9.477841  6.764111 
23.088085  1.721886 23.157911 42.952866 20.572531 32.428322 13.168096 21.318363  2.112123 18.522474 
37.482483 21.273062 10.824656  7.056351  1.929984 47.423546 15.042005  7.827682  0.525395 23.743942 
13.976241 22.684605 56.273182 19.433304  1.251396 12.572036 50.317101  1.306394 30.255325  7.037494 
 8.621302 12.489408  9.532479  0.734043  8.544891  0.437274 36.454865 35.441429 22.615372 55.819672 
11.380870 14.835221 18.000803 38.197777 34.409645 23.131359 28.420401  8.604728  0.187185 30.692186 
 0.911866 14.354537 12.427342 83.447571  2.870197 14.823359 12.002151  1.086884 17.670424  5.251925
*/

