/* Ryan Blair
 * Assignment 6
 * Sate: 11/4/15
 * This file directs the interface between the user pushing and popping elements
 * from the stack.
 */
#include <stdio.h>
#include "stack.h"

char option;
int pushed;
int popped;

int main() {
   counter = 0;
   printf("Welcome to the stack program.\n");
   while(option != 'x') {		/*directs menu for user choice*/
      printf("\nEnter option: ");
      scanf(" %c", &option);
      switch(option) {
	 case 'u':  /*push*/
	    printf("What number? ");
            scanf(" %d", &pushed);
	    if(push(pushed) == 0)
	       printStack(mode);
	    else {  /*pushed beyond size of array, overflow occurs*/
	       printf("Overflow!!!\n");
	       printStack(mode);
            }
	    break;

         case 'o': /*pop*/
            if(pop(&popped) == 0) {
 	       printf("Popped %d\n", popped);
	       printStack(mode);
	    }
	    else { /*not enough elements, underflow occurs*/
	       printf("Underflow!!!\n");
	       printStack(mode);
	    }
            break;
         
         case 'h': /*print in hex*/
            mode = 1;
	    printStack(mode);
	    break;
 
         case 'c': /*print in char*/
	    mode = 2;
	    printStack(mode);
	    break;

         case 'd': /*print in decimal*/
            mode = 0;
	    printStack(mode);
            break;

         case 'x': /*exit*/
            printf("Goodbye!\n");
            break;

         default: /*invalid choice - no output*/
            printf("\n");
	    break;
      }
   }
   return 0;
}
