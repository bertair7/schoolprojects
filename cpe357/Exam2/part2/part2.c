#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memmon.h"

int getLine(char **line, FILE *file) {
   int size, in, i, flag;
   
   size = 20;
   flag = 0;
   *line = (char *) malloc(sizeof(char) * size);

   if (*line == NULL) { 
      fprintf(stderr, "Cannot allocate memory\n");
      exit(EXIT_FAILURE);
   }

   i = 0;
   
   while ((in = getc(file)) != EOF) {
      if (in == '\n') {
         in = 0;
         line[0][i] = in;
         flag = 1;
         break;
      }
      else {
         line[0][i] = in;
         flag = 1;
         i++;
      
         if (i == size-1) {
            size *= 2;
            *line = (char *) realloc(*line, sizeof(char) * size);
         }
      }
   }

   if (i != size-1) {
      *line = (char *) realloc(*line, sizeof(char) * i+1);
   }

   if (flag)
      return 1;
   return EOF;
}
