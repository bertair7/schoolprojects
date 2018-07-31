/** Ryan Blair
 *  Assignment 8
 *  Date 12/4/15
 */
#ifndef GREP_H
#define GREP_H
#define MAX_CHAR 101
typedef struct nodes Node;

/*linked list node*/
struct nodes{
   char line[MAX_CHAR];
   int lineNumber;
   int wordNumber;
   Node *next;
};

int main(int argc, char *argv[]);
/*adds new entry to linked list*/
void addEntry(char *nextLine, int lineNumb, int wordNumb);
/*prints out all linked list nodes starting at root*/
void printLines(Node *root);
#endif
