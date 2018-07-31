#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ui.h"
#include "hashtable.h"

#define SIZE 9973

int checkNFlag(int argc, char **argv) {
   int i, n;

   n = 10;
   for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 'n' && argv[i][2] > '0') {
         n = argv[i][2];
         break;
      }
      else if (argv[i][0] == '-') {
         fprintf(stderr, "Usage: wf [-nX] [file...]\n");
         exit(EXIT_FAILURE);
      }
   }
   return n;
}

char *findFile(int argc, char **argv, int *i) {
   char *inFile;

   for (; *i < argc; (*i)++) {
      if (argv[*i][0] != '-') {
         inFile = argv[*i];
         return inFile;
      }
   }
   return NULL;
}

FILE *checkInputFile(int argc, char **argv, int *i) {
   FILE *input;
   char *inFile;
   
   inFile = findFile(argc, argv, i);
   if (inFile == NULL)
      return NULL;

   input = fopen(inFile, "r");
   if (input == NULL) {
      fprintf(stderr, "wf: %s: ", inFile);
      perror("");
      exit(EXIT_FAILURE);
   }
   return input;
}

int main(int argc, char **argv) {
   int nFlag, i, uniqueWords, totalWords;
   unsigned tableSize;
   FILE *input;
   Hash *table;

   i = 1;
   uniqueWords = 0;
   totalWords = 0;
   table = NULL;
   tableSize = SIZE;

   if (argc > 1) {
      input = checkInputFile(argc, argv, &i);
      nFlag = checkNFlag(argc, argv);
      while (input != NULL) {
         table = getWords(input, &tableSize, &totalWords, &uniqueWords, table);
         i++;
         input = checkInputFile(argc, argv, &i);
      }
   }
   else {
      input = stdin;
      nFlag = checkNFlag(argc, argv);
      table = getWords(input, &tableSize, &totalWords, &uniqueWords, table);   
   }

   table = sortWords(tableSize, uniqueWords, table);
   printWords(table, nFlag, totalWords, uniqueWords);

   return 0;
}
