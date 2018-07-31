/*
 * Provided child program for pipe-fork-exec exercise.
 *
 *    !!! DO NOT MODIFY !!!
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE_MSG 100

static void readMessage(int fd, char *msg)
{
   int i = 0;

   /* Read in an entire string, including the null-termination */
   while(1)
   {
      /* Note that this will block until there is something to read */
      if (1 != read(fd, &msg[i], 1))
      {
         fprintf(stderr, "read failure in %s at line %d\n", __FILE__, __LINE__);
         exit(EXIT_FAILURE);
      }

      if (msg[i] == 0)
         break;

      i++;
   }
}

static void writeMessage(int fd, const char *msg)
{
   int len = strlen(msg) + 1;

   if (len != write(fd, msg, len))
   {
      fprintf(stderr, "write failure in %s at line %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   }
}

static int getFD(const char *arg)
{
   int fd;

   if (1 != sscanf(arg, "%d", &fd))
   {
      fprintf(stderr, "Bad fd argument\n");
      exit(EXIT_FAILURE);
   }

   return fd;
}

int main(int argc, char **argv)
{
   int readFD, writeFD, msgCount = 0;
   char inMsg[SIZE_MSG], outMsg[SIZE_MSG];

   if (argc != 3)
   {
      fprintf(stderr, "Usage: child readFD writeFD\n");
      exit(EXIT_FAILURE);
   }

   readFD = getFD(argv[1]); 
   writeFD = getFD(argv[2]); 
   
   /* Send a "birth-announcement" to the parent */
   sprintf(outMsg, "I'm alive! Reading from %d, writing to %d",
      readFD, writeFD);
   writeMessage(writeFD, outMsg); 

   /* Loop until my parent tells be to quit... */
   while(1)
   {
      /* This read will block until a message is sent */
      readMessage(readFD, inMsg);
   
      /* Send an acknowledgement to the parent */
      sprintf(outMsg, "Message %d: %s", ++msgCount, inMsg);
      writeMessage(writeFD, outMsg); 

      if (0 == strcmp("quit", inMsg))
         break;
   }

   /* Done! */
   sprintf(outMsg, "Okay, I love you, goodbye!");
   writeMessage(writeFD, outMsg); 

   return EXIT_SUCCESS;
}
