#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "wordcount.h"
#include "ui.h"

Inputs wordCount(FILE *file, Inputs input, int i) {
   int chars=0, words=0, lines=0, flag=0, inputChar;

   while ((inputChar = getc(file)) != EOF) {
      chars++;
      if (isprint(inputChar) && !isspace(inputChar)) {
         flag = 1;
      }
      if (isspace(inputChar) && flag) {
         words++;
         flag = 0;
      }
      if (inputChar == '\n') {
         lines++;
         flag = 0;
      }
   }
   if (flag)
      words++;

   input.totalChars += chars;
   input.totalWords += words;
   input.totalLines += lines;
   
   determineReport(input.lFlag, lines, input.wFlag, words, input.cFlag, chars, 
      input.names[i]);
   
   return input;
}

