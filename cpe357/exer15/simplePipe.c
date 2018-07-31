#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define QUIT 'q'
#define NEW_PIPE 'n'
#define WRITE_TO_PIPE 'w'
#define READ_FROM_PIPE 'r'
#define CLOSE_PIPE_END 'c'

static void badResult() {
   perror(NULL);
   exit(EXIT_FAILURE);
}

static void createNewPipe() {
   int newpipe[2];

   pipe(newpipe);
   printf("Pipe successfully created, read-fd is %d, write-fd is %d\n", 
      newpipe[0], newpipe[1]);
}

static void writeToPipe() {
   int result, writeEnd, num;

   printf("Enter the fd of the write-end to write to: ");
   scanf("%d", &writeEnd);
   printf("Enter the integer value you wish to write: ");
   scanf("%d", &num);

   result = write(writeEnd, &num, sizeof(num));

   if (result > -1)
      printf("The value %d was written successfully to fd %d\n", num, 
         writeEnd);
   else 
      badResult();
}

static void readFromPipe() {
   int result, readEnd, num;

   printf("Enter the fd of the read-end to read from: ");
   scanf("%d", &readEnd);
   
   result = read(readEnd, &num, sizeof(num));

   if (result > -1)
      printf("The value %d was read successfully from fd %d\n", num, readEnd);
   else
      badResult();
}

static void closePipeEnd() {
   int result, end;
 
   printf("End the fd of the pipe-end you wish to close: ");
   scanf("%d", &end);

   result = close(end);
   
   if (result == 0) 
      printf("File descriptor %d successfully closed\n", end);
   else
      badResult();
}

static int getCommand()
{
   char command;

   printf("\nCommand Menu:\n");
   printf("   n - Create a new pipe\n");
   printf("   w - Write to a pipe end\n");
   printf("   r - Read from a pipe end\n");
   printf("   c - Close a pipe end\n");
   printf("   q - Quit\n\n");
   printf("Enter a command: ");

   /* I know, this expects the user to be perfect - hey it's an exercise! */
   scanf(" %c", &command);
   return command;
}

static int doACommand()
{
   char command = getCommand();
   
   switch (command)
   {
      case NEW_PIPE:
         createNewPipe();
      break;

      case WRITE_TO_PIPE:
         writeToPipe();
      break;

      case READ_FROM_PIPE:
         readFromPipe();
      break;

      case CLOSE_PIPE_END:
         closePipeEnd();
      break;

      case QUIT:
         printf("Bye Bye - see you next time!\n");
      break;

      default:
         printf("Unknown command, please try again...\n");
   }

   return command;
}

/*
 * NOTE: The SIGPIPE signal is ignored in this program so that you can see the
 *       error that occurs when you try to write to a pipe whose read-end is
 *       closed - be sure to try that scenario!
 */
int main()
{
   int command = !QUIT;

   /* See comment block preceding main */
   signal(SIGPIPE, SIG_IGN);

   while (command != QUIT)
      command = doACommand();

   return 0;
}
