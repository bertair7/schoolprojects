#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ui.h"

int checkFlag(int argc, char *argv[], char *lwcFlag) {
   int flag, i;

   flag = 0;

   for (i = 1; i < argc; i++) {
      if (strcmp(argv[i], lwcFlag) == 0) {
         flag = 1;
         break;
      }
   }
   return flag;
}

void printFlagError(char *error) {
   fprintf(stderr, "swc: invalid option: '%s'\n", error);
   fprintf(stderr, "Usage: swc [-l|-w|-c]... [file]...");
   exit(EXIT_FAILURE);
}

void printFileError(char *error) {
   fprintf(stderr, "swc: ");
   perror(error);
   exit(EXIT_FAILURE);   
}

void determineReport(int l, int lines, int w, int words, int c, int chars, 
   char *fileName) {
   if (l)
      printf("%10u", lines);
   if (w) {
      if (l)
         printf("%11u", words);
      else
         printf("%10u", words);
   }
   if (c) {
      if (l || w)
         printf("%11u", chars);
      else
         printf("%10u", chars);
   }
 
   if (strcmp(fileName, "") != 0)
      printf(" %s", fileName);
   printf("\n");
}

void determineTotalReport(Inputs input) {
   char string[] = "total";

   if (input.lFlag)
      printf("%10u ", input.totalLines);
   if (input.wFlag)
      printf("%10u ", input.totalWords);
   if (input.cFlag)
      printf("%10u ", input.totalChars);
   printf("%s\n", string);
}
