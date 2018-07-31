#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 100

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

int main(int argc, char **argv) {
   char wline[MAXLINE], rline[MAXLINE], rd[2], wd[2];
   int fd[2], cp[2];
   pid_t pid;

   if (pipe(fd) == -1) {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   if (pipe(cp) == -1) {
      perror(NULL);
      exit(EXIT_FAILURE);
   }

   sprintf(rd, "%d", fd[0]);
   rd[1] = 0;
   sprintf(wd, "%d", cp[1]);
   wd[1] = 0;

   pid = fork();

   if (pid < 0) {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if (pid == 0) { /*child*/
      execl(argv[1], argv[1], rd, wd, (char *)0);
      readMessage(fd[0], rline);
      writeMessage(cp[1], wline);
   }
   else { /*parent*/
      readMessage(cp[0], rline);
      printf("%s\n", rline);

      while (1) {
         printf("Enter a message for the child: ");

         fgets(wline, MAXLINE, stdin);
         if (wline[strlen(wline) - 1] == '\n')
            wline[strlen(wline) - 1] = 0;
         writeMessage(fd[1], wline);
         
         readMessage(cp[0], rline);
         printf("%s\n", rline);

         if (strcmp("quit", wline) == 0)
            break;
      }

      fprintf(stderr, "couldn't execute: %s\n", wline);
      exit(EXIT_FAILURE);
   }
   exit(EXIT_SUCCESS);
}
