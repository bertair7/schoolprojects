#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "hashtable.h"
#include <stdio.h>

static int isPrime(unsigned x) {
   int i;

   for (i = 2; i < sqrt(x); i++) {
      if ((x % i) == 0)
         return 0;
   }
   return 1;
}

static unsigned nextPrime(unsigned x) {
   if ((x % 2) == 0)
      x++;
   while (!isPrime(x))
      x += 2;

   return x;
}

/* lose lose hash algorithm listed on
 * www.cse.yorku.ca/~oz/hash.html and 1st ed. of K&R
 */

static unsigned long getKey(char *str, unsigned length) {
   unsigned long key = 0;
   int i, c;

   for (i = 0; i < length; i++) {
      c = *str++;
      key += c;
   }
   return key;
}

static int getHashCode(char *word, unsigned length, unsigned long key, 
   Hash *table, unsigned tableSize) {
   int i, hashCode;
   Hash temp;

   hashCode = key % tableSize;
   i = 1;
   temp = table[hashCode];

   while (temp.key) {
      if (temp.wordLength == length && memcmp(temp.word, word, temp.wordLength)
         == 0) 
         break;
      hashCode += i;
      hashCode %= tableSize;
      i++;
      temp = table[hashCode];
   }

   return hashCode;
}

static Hash *rehashTable(Hash *table, unsigned *tableSize) {
   int i;
   unsigned newTableSize;
   Hash *temp;

   newTableSize = nextPrime(2 * *tableSize);
   temp = table;
   table = (Hash *) malloc(sizeof(Hash) * newTableSize);

   for (i = 0; i < *tableSize; i++) {
      if (temp[i].key) 
         table[i] = temp[i]; 
   }

   free(temp);
   *tableSize = newTableSize;
   return table;
}

int compareHash(const void *first, const void *second) {
   Hash *one = (Hash *) first, *two = (Hash *) second;
   int string;

   if (one->count > two->count)
      return -1;
   else if (one->count < two->count)
      return 1;

   string = memcmp(one->word, two->word, one->wordLength);
   if (string > 0)
      return 1;
   else if (string < 0)
      return -1;

   return 0;
}

int findWord(char **word, unsigned length, Hash *table, unsigned tableSize) {
   int hashCode;
   unsigned long key;
   Hash temp;

   key = getKey(*word, length);
   hashCode = getHashCode(*word, length, key, table, tableSize);
   temp = table[hashCode];

   if (temp.key) {
      table[hashCode].count += 1;
      return 1;
   }

   return 0;
}

Hash *insert(char **word, unsigned length, Hash *table, unsigned *tableSize, 
   int words) {
   Hash temp;
   int hashCode;

   temp.key = getKey(*word, length);
   temp.count = 1;
   temp.word = *word;
   temp.wordLength = length;
   
   hashCode = getHashCode(temp.word, temp.wordLength, temp.key, table, 
      *tableSize);
   table[hashCode] = temp;

   if (words >= (*tableSize / 2))
      table = rehashTable(table, tableSize);
   return table;
}
