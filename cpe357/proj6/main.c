#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "trie.h"
#include "bit.h"

static void printError() {
   fprintf(stderr, "Usage: lzwCompress [-rN] file\n");
   fprintf(stderr, "Where: N is a number from 9 to 15 specifying the");
   fprintf(stderr, " recycle code as a power of 2\n");
   exit(EXIT_FAILURE); 
}

static void checkArgs(int argc, char *argv[], int *r, char **fileName) {
   int i;

   if (argc < 2 || argc > 3)
      printError();
   
   for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 'r') {
         *r = atoi(&argv[i][2]);
         if (*r < 9 || *r > 15)
            printError();
      }
      else if (argv[i][0] != '-') 
         *fileName = argv[i];
      else
         printError();
   }
}

static FILE *openFile(char *name) {
   FILE *file;

   file = fopen(name, "r");
   if (file == NULL) {
      fprintf(stderr, "lzwCompress: %s: ", name);
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   return file;
}

static int checkFileSize(FILE *input) {
   int size;

   if (input != NULL) {
      fseek(input, 0, SEEK_END);
      size = ftell(input);
      rewind(input);
   }
   return size;
}

int main(int argc, char *argv[]) {
   int rFlag = 12, limit, size;
   char *fileName, outFile[50], *lzw = ".lzw";
   FILE *input, *output;

   checkArgs(argc, argv, &rFlag, &fileName);
   input = openFile(fileName);
   size = checkFileSize(input);

   strcpy(outFile, fileName);
   strcat(outFile, lzw);

   if (size != 0) {
      limit = pow(2, rFlag);
      compressLZW(input, outFile, rFlag, limit);
   }
   else { 
      output = fopen(outFile, "w");
      fclose(input);
      fclose(output);
   }
   
   return EXIT_SUCCESS;
}
