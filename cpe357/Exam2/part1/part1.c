#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
   int count, find;
   char chr;
   FILE *in;

   if (argc != 3) {
      fprintf(stderr, "Usage: countBytes fileName byteValue\n");
      exit(EXIT_FAILURE);
   }

   in = fopen(argv[1], "r");
   if (in == NULL) {
      perror(argv[1]);
      exit(EXIT_FAILURE);
   }
   
   count = 0;
   find = atoi(argv[2]);

   while ((chr = getc(in)) != EOF) {
      if (find == chr)
         count++;
   }

   printf("The byte value %d appears %d times in %s\n", find, count, 
      argv[1]);
   
   return 0;
}
