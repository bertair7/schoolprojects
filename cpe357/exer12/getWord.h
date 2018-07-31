#ifndef GETWORD_H
#define GETWORD_H
/* 
 * PROVIDED CODE FOR EXERCISE 12
 * !!! DO NOT MODIFY !!!
 * YOU MAY USE THIS CODE IN YOUR PROJECT SOLUTION IF YOU WISH.
 *
 * Inspired by the non-standard GNU getline function and intended for use
 * in Project 3: Word Freq.
 *
 * This function reads a word from the specified file and puts it in a
 * dynamically allocated chuck of memory, and returns via the "output
 * parameters" the address of the "word", its length, and whether or not it
 * contains any printable characters (determined by isprint in ctype.h)
 *
 *    Notice that the resulting "word" IS NOT a C-string, i.e., it is not
 *    zero-terminated! You MAY NOT USE any of the "str" functions found in
 *    string.h in your solution. Instead, you must use the "mem" functions
 *    (also found in string.h).
 *
 * A FEW IMPORTANT DETAILS...
 *
 *    1. "Words" are defined exactly they are in Project 2.
 *    2. "Words" are converted to all lowercase (use tolower in ctype.h).
 *    3. The allocated memory will be exactly the same as the length of the
 *       word when returned. Start with a small allocation and grow it as
 *       necessary logarithmically - don't forget to trim it before returning.
 *    4. You will find realloc very helpful for growing and shrinking memory
 *       allocations. BE AWARE THAT realloc SOMETIMES RETURNS THE SAME ADDRESS
 *       AND SOMETIMES RETURNS A NEW ADDRESS - you need to handle this
 *       correctly! Also, if you request a size of zero it frees the current
 *       allocation and returns NULL.
 *    5. For your own sanity you should check and handle (perror, exit) any
 *       file or memory errors - text of your choice, won't be tested in
 *       this exercise but may be tested in Project 3.
 *    6. Returns EOF when the end of file is encountered, otherwise 0.
 */

int getWord(char **word, unsigned *wordLength, FILE* file,
   const char *fileName); 

#endif
