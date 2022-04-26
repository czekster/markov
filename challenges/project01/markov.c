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

float** validate(char* filename, char type, int* size) {
   int state = 0;
   *size = find_order(filename);

   float** m = create_matrix(*size);

   init_matrix(m, 0.0, *size);
   int result = open_model(filename, m);
   switch (result) {
      case ERR_NOT_SQUARE:
         printf("Error: matrix is not square (lines != columns).\nTry again.\n");
         destroy_matrix(m, *size);
         exit(1);
   }
   result = validate_mc(m, *size, &state, type); 
   switch (result) {
      case ERR_LINE_SUM:
         printf("Error: line does NOT sum 1.0.\nTry again.\n");
         destroy_matrix(m, *size);
         exit(1);
      case ERR_ABSORBING:
         printf("Error: chain with absorbing state (state=%d).\nTry again.\n", state);
         destroy_matrix(m, *size);
         exit(1);
      case SUCCESS:
         printf("Success: that is one well-formed dtmc matrix.\n");
         break;
   }
   return m;
}

int validate_mc(float** m, int size, int* state, char type) {
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
      //printf("type=%c i=%d in=%d out=%d m[%d][%d]=%f\n", type, i, incoming, outgoing, i, i, m[i][i]);
      if (type == 'd' && line_sum < 0.99 && line_sum > 1.01)
         return ERR_LINE_SUM;
      else
      if ((outgoing == 1 && m[i][i] > 0) || (incoming == 1 && outgoing == 0))
         return ERR_ABSORBING;
   }
   return SUCCESS;
}

