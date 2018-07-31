#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static TrieNode *createNode() {
   int i;
   TrieNode *newNode;

   newNode = (TrieNode *) malloc(sizeof(TrieNode));
   if (newNode == NULL) {
      fprintf(stderr, "Malloc failure\n");
      exit(EXIT_FAILURE);
   }

   for (i = 0; i < NUMBER_OF_SYMBOLS; i++) {
      newNode->code[i] = USHRT_MAX;
      newNode->next[i] = NULL;
   }
   return newNode;
}

TrieNode *createNewTrie() {
   Code i;
   TrieNode *root = (TrieNode *) malloc(sizeof(TrieNode));

   if (root == NULL) {
      fprintf(stderr, "Malloc failure\n");
      exit(EXIT_FAILURE);
   }

   for (i = 0; i < NUMBER_OF_SYMBOLS; i++) {
      root->code[i] = i;
      root->next[i] = createNode();
   }
   return root;
}

/* Insert and Search Trie functions based on completed functions from 
 * geeksforgeeks.org/trie-insert-and-search
 */
void addToTrie(char *str, Code index, TrieNode *root, int length) {
   int c;
   int i = 0;
   TrieNode *current = root, *newNode = createNode();

   while (i < length) {
      c = str[i];
      if (c < 0)
         c = (unsigned char) c;
      i++;

      if (current->next[c] == NULL) {
         current->code[c] = index;
         current->next[c] = newNode;
         break;
      }
      current = current->next[c];
   }
}

Code searchTrie(char *str, TrieNode *root, int length) {
   int i, c;
   Code index;
   TrieNode *current = root;

   for (i = 0; i < length; i++) {
      c = str[i];
      if (c < 0)
         c = (unsigned char) c;

      if (current == NULL)
         return USHRT_MAX;
      if (current->code[c] == USHRT_MAX)
         return USHRT_MAX;

      index = current->code[c];
      current = current->next[c];
   }

   return index;
}

void freeTrie(TrieNode *root) {
   int i;

   for (i = 0; i < NUMBER_OF_SYMBOLS; i++) {
      if (root->next[i] != NULL)
         freeTrie(root->next[i]);
   }
   free(root);  
}
