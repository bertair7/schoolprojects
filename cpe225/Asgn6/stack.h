/* Ryan Blair
 * Assignment 6
 * Date: 11/4/15
 * The stack controls the elements being pushed in and popped out.  The array
 * keeps track of the elements, while the counter points to the top element
 * in the stack. The mode controls how the output will be viewed by the user.
 */
#ifndef STACKH
#define STACKH

int push(int value);
int pop(int *value);
void printStack(int val);
int array[10];
int counter;
int mode;
#endif
