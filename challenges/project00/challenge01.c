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

// Author: Ricardo M. Czekster (rczekster@gmail.com)
// Date: 11/03/2022

// Compile with: gcc -o challenge01 challenge01.c 
// Execute with: ./challenge01 10
//    (this will generate 10 random numbers from 0 to 1)

// prototypes
float uniform(void);
void showN_uniform(int);

// main function
int main(int argc, char *argv[]) {

   srand(time(NULL)); // init seed (using current time - this will produce different numbers every time)
   if (argc != 2) {
      printf("Usage: challenge01 <PARAMETER>\n \
              where PARAMETER is the number of values to compute.\n");
      exit(1);
   }
   int number = atoi(argv[1]); // converts the number from a string (array of chars) from the command line to integer
   printf("Computing %d numbers from the uniform distribution...\n", number);

   showN_uniform(number);

   return 0;
}

// implementations

float uniform() {
    return (random()/(float)RAND_MAX); // this makes the number stay between 0 and 1
}

void showN_uniform(int n) {
   for (int i=0; i < n; i++) {
      float random_number = uniform();
      printf("%f ", random_number);
      if ((i+1) % 10 == 0)
         printf("\n"); // print 10 numbers then add a \n
   }
}


// input and output

/*
$ ./challenge01 100
Computing 100 numbers from the uniform distribution...
0.193676 0.468163 0.810230 0.508471 0.984274 0.617850 0.301160 0.983740 0.591864 0.170534 
0.875797 0.729701 0.008773 0.463273 0.397333 0.974192 0.136513 0.765968 0.788955 0.606030 
0.345244 0.377442 0.371363 0.946249 0.421087 0.305751 0.093021 0.447245 0.007869 0.165619 
0.165420 0.201544 0.633782 0.975650 0.710015 0.618056 0.593500 0.011175 0.601797 0.185363 
0.181709 0.477593 0.915064 0.190481 0.940866 0.312397 0.164673 0.077380 0.078365 0.953628 
0.683410 0.423609 0.331071 0.054773 0.369859 0.752158 0.360524 0.462880 0.199403 0.368392 
0.628500 0.364823 0.569937 0.262282 0.340473 0.279952 0.880338 0.933973 0.291127 0.482135 
0.119336 0.472835 0.959728 0.034400 0.663316 0.900594 0.346797 0.827990 0.977974 0.425163 
0.781618 0.661384 0.848772 0.112689 0.716157 0.218631 0.864847 0.076681 0.681511 0.064249 
0.445073 0.310010 0.429072 0.015010 0.572292 0.769545 0.294962 0.452631 0.703518 0.586089 

*/
