#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wordcount.h"
#include "ui.h"

int checkFlags(Inputs input, char *arg) {
   if (arg[1] == 'w' || arg[1] == 'l' || arg[1] == 'c') 
      return 0;
   
   return 1;
}

Inputs getInputStream(int argc, char *argv[]) {
   int i, j = 0, flagerr = 0;
   char *error;
   Inputs input;

   input.total = 0;

   if (argc == 1) {
      input.names[0] = "";
      input.total++;
      return input;
   }

   for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
         if ((flagerr = checkFlags(input, argv[i])) == 1) {
            error = argv[i];
            break;
         }
      }
      else {
         input.names[j] = argv[i];
         input.total++;
         j++;
      }
   }

   if (flagerr == 1) 
      printFlagError(error);

   return input;
}

Inputs getFlags(int argc, char *argv[], Inputs input) {
   char lFlag[] = "-l", wFlag[] = "-w", cFlag[] = "-c";

   input.totalLines = 0;
   input.totalWords = 0;
   input.totalChars = 0;
   input.lFlag = checkFlag(argc, argv, lFlag);
   input.wFlag = checkFlag(argc, argv, wFlag);
   input.cFlag = checkFlag(argc, argv, cFlag);
   
   if (!input.lFlag && !input.wFlag && !input.cFlag) {
      input.lFlag = 1;
      input.wFlag = 1;
      input.cFlag = 1;
   }
   return input;
}

int main(int argc, char *argv[]) {
   Inputs input;
   FILE *file;
   int i;

   input = getInputStream(argc, argv);
   input = getFlags(argc, argv, input);

   if (input.total == 1 && strcmp(input.names[0], "") == 0) {
      file = stdin;
      input = wordCount(file, input, 0);
   }
   else {
      for (i = 0; i < input.total; i++) {
         file = fopen(input.names[i], "r");
         if (file != NULL)
            input = wordCount(file, input, i);
         else
            printFileError(input.names[i]);
      }
   }

   if (input.total > 1)
      determineTotalReport(input);

   return 0;
}

