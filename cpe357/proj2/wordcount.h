#include <stdlib.h>
#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#define MAXNAMES 100

typedef struct {
   char *names[MAXNAMES];
   int lFlag;
   int wFlag;
   int cFlag;
   int totalLines;
   int totalWords;
   int totalChars;
   int total;
} Inputs;

Inputs wordCount(FILE *file, Inputs input, int i);

#endif
