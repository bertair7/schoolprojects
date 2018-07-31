#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
   char args[101];
   int totalChar, i, j, k, flag;

   if (argc == 1) {
      fprintf(stdout, "Usage: reference arg [arg...]\n");
      exit(EXIT_FAILURE);
   }

   totalChar = 0;
   flag = 0;
   k = 0;

   for (i = 1; i < argc; i++) {
      j = 0;
      while (argv[i][j] != '\0') {
         totalChar++;
         if (totalChar > 100) {
            flag = 1;
            break;
         }
         args[k] = argv[i][j];
         k++;
         j++;
      }   
   }

   if (flag) {
      fprintf(stderr, "Quitting, string exceeds 100 characters\n");
      exit(EXIT_FAILURE);
   }
   args[k] = '\0';

   fprintf(stdout, "%s\n", args);
   return 0;
}
