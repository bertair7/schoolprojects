#ifndef TRIE_H
#define TRIE_H

#define NUMBER_OF_SYMBOLS 256

typedef unsigned short Code;
typedef struct trieNode {
   Code code[NUMBER_OF_SYMBOLS];
   struct trieNode *next[NUMBER_OF_SYMBOLS];
} TrieNode;

TrieNode *createNewTrie();
void addToTrie(char *str, Code index, TrieNode *root, int length);
Code searchTrie(char *str, TrieNode *root, int length);
void freeTrie(TrieNode *root);

#endif
