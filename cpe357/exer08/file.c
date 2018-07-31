#include <stdio.h>
#include <string.h>

FILE* fileOpen(const char *fname) {
   FILE *fp;

   fp = fopen(fname, "r");

   if (fp == NULL) {
      fprintf(stderr, "\n%s: ", fname);
      perror("");
   }
   
   return fp;
}

void fileDump(FILE *file, const char *fname) {
   int input;

   printf("\n%s:\n", fname);
   
   while ((input = getc(file)) != EOF) {
      putchar(input);
   }
}
