#include "hashtable.h"
#ifndef UI_H
#define UI_H

Hash *getWords(FILE *input, unsigned *tableSize, int *totalWords, 
   int *uniqueWords, Hash *table);
Hash *sortWords(unsigned tableSize, int uniqueWords, Hash *table);
void printWords(Hash *sorted, int n, int totalWords, int uniqueWords);


#endif
