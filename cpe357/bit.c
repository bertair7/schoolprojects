#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include "bit.h"
#include "trie.h"

static void checkString(char *str) {
   if (str == NULL) {
      free(str);
      perror(NULL);
      exit(EXIT_FAILURE);
   }
}

static int calcPrintBytes(int *left, int r) {
   int numBytes, totalBits;

   totalBits = *left + r;
   numBytes = totalBits / 8;
   *left = totalBits - (numBytes * 8);

   return numBytes;
}

static unsigned newBuffer(unsigned buffer, int *overflow, int *left, int r, 
   Code index) {
   buffer = buffer | *overflow;
   buffer = buffer << r;

   buffer = buffer | index;
   buffer = buffer << ((sizeof(unsigned) * 8) - r - *left);

   return buffer;
}

static void printBuffer(unsigned buffer, int printBytes, FILE *output) {
   unsigned mask = 0xFF;
   unsigned char print;
   
   if (printBytes == 1) {
      mask = mask << (sizeof(unsigned) * 8 - 8);
      mask = mask & buffer;
      mask = mask >> (sizeof(unsigned) * 8 - 8);

      print = mask; 
      /*fprintf(stderr, "mask = %X, printing out %X\n", mask, print);*/
      fwrite(&print, sizeof(char), sizeof(char), output);
   }
   else {
      printBuffer(buffer, 1, output);
      buffer = buffer << 8;
      printBuffer(buffer, printBytes - 1, output);
   }
}

static Code calcNewOverflow(int *left, Code index) {
   int shift;

   shift = (sizeof(Code) * 8) - *left;
   index = index << shift;
   index = index >> shift;

   return index;
}

static void printToFile(char *str, TrieNode *root, int length, int *left, 
   int *overflow, int r, FILE *output) {
   int printBytes;
   unsigned buffer = 0;
   Code index;

   /*fprintf(stderr, "str = %s\n", str);*/
   index = searchTrie(str, root, length);
   if (index == USHRT_MAX)
      index = 256;
   /*fprintf(stderr, "index = %d\n", index);*/

   buffer = newBuffer(buffer, overflow, left, r, index);
   /*fprintf(stderr, "buffer = %X\n", buffer);*/
   printBytes = calcPrintBytes(left, r);
   printBuffer(buffer, printBytes, output);

   *overflow = calcNewOverflow(left, index);
   /*fprintf(stderr, "left = %d, overflow = %X\n", *left, *overflow);*/
}

static char *addToString(char *str, int length, const char *src, char add) {
   str = (char *) realloc(str, length * sizeof(char));
   checkString(str);

   memcpy(str, src, length-1);
   str[length-1] = add;
   str[length] = 0;

   return str;
}

static void closeFiles(int *left, int *overflow, int currR, FILE *input, 
   FILE *output) {
   Code end = 256;
   unsigned buffer = 0;

   buffer = newBuffer(buffer, overflow, left, currR, end);
   printBuffer(buffer, 2, output);
 
   fclose(input);
   fclose(output);
}

void compressLZW(FILE *input, char *file, int r, int limit) {
   char *previous, *current;
   int c, length = 0, left = 0, overflow = 0, currR = 9;
   Code index, next = NUMBER_OF_SYMBOLS + 1;
   FILE *output = fopen(file, "w");
   TrieNode *root = createNewTrie();

   previous = (char *) malloc(sizeof(char));
   checkString(previous);
   current = (char *) malloc(sizeof(char));
   checkString(current);
 
   printToFile((char *) &r, root, 1, &left, &overflow, 8, output);

   while ((c = fgetc(input)) != EOF) {
      /*fprintf(stderr, "c = %d\n", c);*/
      length++;
      current = addToString(current, length, previous, (char)c);
      index = searchTrie(current, root, length);

      if (index == USHRT_MAX) {
         addToTrie(current, next, root, length);
         printToFile(previous, root, length-1, &left, &overflow, currR, output);
         next++;
         length = 1;
      }
      previous = addToString(previous, length, previous, (char)c);

      if (next == limit + 1) {
         freeTrie(root);
         root = createNewTrie();
         next = NUMBER_OF_SYMBOLS + 1;
         currR = 9;
      }

      if (next == (pow(2, currR) + 1)) 
         currR++;
   }
   /*fprintf(stderr, "end of file\n");*/
   printToFile(previous, root, length, &left, &overflow, currR, output);
   /*fprintf(stderr, "closing files, writing out last output\n");*/
   closeFiles(&left, &overflow, currR, input, output);

   free(previous);
   free(current);
   freeTrie(root);
}
