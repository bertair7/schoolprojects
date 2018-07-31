/** Ryan Blair
 *  Assignment 8
 *  Date 12/4/15
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myGrep.h"

/*global variables for access between methods*/
Node *root;
Node *temp;
int times;

int main(int argc, char *argv[]) {
   FILE *infile;
   char longestLine[MAX_CHAR];
   char line[MAX_CHAR]; 
   char linecpy[MAX_CHAR];
   char *lword;
   int tempLen;
   int i;
   int lines = -1;
   int longest = 0;
   times = 0;

   /*check for appropriate amount of arguments*/
   if(argc != 3) {	/*too many/few*/
      printf("myGrep: improper number of arguments");
      printf("\nUsage: %s <filename> <word>\n", argv[0]);
      return 1;
   }
   else {		/*unable to open file*/
      infile = fopen(argv[1], "r");
      if(infile == 0) {
	 printf("Unable to open file: %s\n", argv[1]);
	 return 1;
      }
      else {		/*correct arguments*/
         while(fgets(line, MAX_CHAR, infile) != NULL) {
            tempLen = strlen(line);
            if(longest < tempLen) { 			/*check for longest line*/
	       longest = tempLen;
	       strcpy(longestLine, line);		/*makes copy*/
            }
            lines++;
	    /*since line will be affected with strtok, create copy for node*/
            strcpy(linecpy, line);			
            lword = strtok(line, " .\n\r");
            i = 0;
            while(lword != NULL) {			/*check for word in line*/
	       if(strcmp(lword, argv[2]) == 0) {
	          addEntry(linecpy, lines, i);		/*node creation*/
               }
	       i++;
               lword = strtok(NULL, " .\n\r");
            }
	 }
	 /*print out other info*/
  	 printf("%s %s %s\n", argv[0], argv[1], argv[2]);
	 printf("longest line: %s", longestLine);
   	 printf("num chars: %d\n", longest);
	 printf("num lines: %d\n", lines+1);
	 printf("total occurrences of word: %d\n", times);
	 /*print remaining lines with word*/
	 printLines(root);
      }
   }
   fclose(infile);
   return 0;
}

/*creates new node to end, using temp as pointer of previous node*/
void addEntry(char *nextLine, int lineNumb, int wordNumb) {
   Node *tempNode;
   int i;

   tempNode = (Node *)malloc(sizeof(Node));
   for(i = 0; i < MAX_CHAR; i++) {
      tempNode->line[i] = nextLine[i];
   }
   tempNode->lineNumber = lineNumb;
   tempNode->wordNumber = wordNumb;
   /*first node is root pointer*/
   if(root == NULL) {
      root = tempNode;
      temp = root;
   }
   else {
      temp->next = tempNode;
   }
   temp = tempNode;
   times++;
}

/*prints out elements iteratively by having root pointer move through list*/
void printLines(Node *root) {
   Node *tempNode;
   while(root != NULL) {
      tempNode = (Node *)malloc(sizeof(Node));
      tempNode = root;
      printf("line %d; word %d; %s", root->lineNumber, root->wordNumber, root->line);
      root = root->next;
      free(tempNode);
   }
}
