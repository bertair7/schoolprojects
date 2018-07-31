#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "memmon.h"
#include "getWord.h"

#define BUFFSIZE 100000

int correctInput(int input) {
   if (isprint(input))
      return tolower(input);
   return 255;
}

int moveMemory(char **word, char *memory, unsigned *wordLength, 
   const char *fileName) {
   *word = (char *) malloc(sizeof(char) * *wordLength);
   memmove(*word, memory, sizeof(char) * *wordLength);
   return 0;
}

int getWord(char **word, unsigned *wordLength, FILE* file, 
   const char *fileName) {
   int flag, in, i;
   char memory[BUFFSIZE];

   flag = 0;
   *wordLength = 0;
   i = 0;

   while ((in = getc(file)) != EOF) {
      if (!isspace(in)) {
         in = correctInput(in);
         memory[i] = in;
         i++;
         (*wordLength)++;
         flag = 1;
      }
      else {
         if (in == ' ' || !isprint(in))
            break;
      }
   }
 
   if (in != EOF) 
      return moveMemory(word, memory, wordLength, fileName);
   else if (flag) 
      return moveMemory(word, memory, wordLength, fileName);

   return EOF;
}

