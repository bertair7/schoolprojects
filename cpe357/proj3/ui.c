#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "ui.h"
#include "hashtable.h"

static void printWord(const char *word, unsigned wordLength) {
   int i;

   for (i = 0; i < wordLength && i < 30; i++) {
      if (isprint(word[i]))
         printf("%c", word[i]);
      else
         printf("%c", 255);
   }
   if (wordLength > 30)
      printf("...\n");
   else
      printf("\n");
}

static int correctInput(int input) {
   if (isprint(input))
      return tolower(input);
   return input;
}

static int moveMemory(char **word, char *memory, unsigned wordLength) {
   *word = (char *) malloc(sizeof(char) * wordLength);
   memmove(*word, memory, sizeof(char) * wordLength);
   free(memory);
   return 0;
}

static int getWord(char **word, unsigned *wordLength, FILE *file) {
   int flag, in, i;
   char *memory;

   flag = 0;
   i = 0;
   *wordLength = 0;
   memory = (char *) malloc(sizeof(char));

   while ((in = getc(file)) != EOF) {
      if (!isspace(in)) {
         if (isprint(in))
            flag = 1;
         in = correctInput(in);
         (*wordLength)++;
         memory = (char *) realloc(memory, sizeof(char) * *wordLength);
         memory[i] = in;
         i++;
      }
      else {
         if (in == ' ' || !isprint(in)) {
            if (flag)
               break;
            else {
               free(memory);
               *wordLength = 0;
               i = 0;
               memory = (char *) malloc(sizeof(char));
            }
         }
      }
   }

   if (in != EOF)
      return moveMemory(word, memory, *wordLength);
   else if (flag)
      return moveMemory(word, memory, *wordLength);

   return EOF;
}

Hash *getWords(FILE *input, unsigned *tableSize, int *totalWords, 
   int *uniqueWords, Hash *table) {
   int unique;
   unsigned length = 0;
   char *string = NULL;

   unique = 0;
   if (table == NULL) 
      table = (Hash *) malloc(sizeof(Hash) * *tableSize);

   while (EOF != getWord(&string, &length, input)) {
      (*totalWords)++;
      if (!findWord(&string, length, table, *tableSize)) {
         (*uniqueWords)++;
         unique++;
         table = insert(&string, length, table, tableSize, unique);
      }
   }
   
   fclose(input);
   return table;
}

Hash *sortWords(unsigned tableSize, int uniqueWords, Hash *table) {
   Hash *sorted, temp;
   int i, j;

   sorted = (Hash *) malloc(sizeof(Hash) * uniqueWords);

   for (i = 0, j = 0; i < tableSize && j < uniqueWords; i++) {
      temp = table[i];
      if (temp.count > 0) {
         sorted[j] = temp;
         j++;
      }
   }
   free(table);
   qsort(sorted, uniqueWords, sizeof(Hash), compareHash);
   return sorted;
}

void printWords(Hash *sorted, int n, int totalWords, int uniqueWords) {
   int i;
   Hash temp;

   printf("%d unique words found in %d total words\n", uniqueWords, 
      totalWords);
    
   if (n > uniqueWords)
      n = uniqueWords;

   for (i = 0; i < n; i++) {
      temp = sorted[i];
      if (temp.count > 100000000)
         n++;
      else {
         printf("%10d - ", temp.count);
         printWord(temp.word, temp.wordLength);
      }
   }

   free(sorted);
}
