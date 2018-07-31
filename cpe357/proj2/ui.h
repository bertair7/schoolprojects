#include "wordcount.h"
#ifndef UI_H
#define UI_H

int checkFlag(int argc, char *argv[], char *lwcFlag);
void printFlagError(char *error);
void printFileError(char *error);
void determineReport(int l, int lines, int w, int words, int c, int chars, 
   char *fileName);
void determineTotalReport(Inputs input);

#endif
