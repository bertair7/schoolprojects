#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct {
   unsigned long key;
   int count;
   char *word;
   unsigned wordLength;
} Hash;

int compareHash(const void *first, const void *second);
int findWord(char **word, unsigned length, Hash *table, unsigned tableSize);
Hash *insert(char **word, unsigned length, Hash *table, unsigned *tableSize, 
   int words);

#endif
