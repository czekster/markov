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
      //printf("line=%s\n",line);
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

