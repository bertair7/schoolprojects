/* Ryan Blair
 * Assignment 6
 * Date: 11/4/15
 */
#include <stdio.h>
#include "stack.h"

int push(int value) {
   if(counter < 10) { /*if counter has room, add element*/
      array[counter] = value;
      counter++;
      return 0;
   }
   else		      /*counter is full, cannot add to array*/
      return 1;
}

int pop(int *value) { 
   if(counter > 0) {  /*pops out last entry added to array*/
      int temp = array[counter-1];
      *value = temp;
      counter--;
      return 0;
   }
   else		     /*array is empty, no element can be popped*/
      return 1;
}

void printStack(int val) { /*val is based on current mode of array*/
   int i;
   if(val == 0) {          
      printf("Stack: "); /*decimal*/
      for(i = 0; i < counter; i++) {
         printf("%d ", array[i]);
      }
      printf("\n");
   }
   else if(val == 1) { /*hex*/
      printf("Stack: ");
      for(i = 0; i < counter; i++) {
         printf("%x ", array[i]);
      }
      printf("\n");
   }
   else if(val == 2) { /*char*/
      printf("Stack: ");
      for(i = 0; i < counter; i++) {
         printf("%c ", array[i]);
      }
      printf("\n");
   }
}
