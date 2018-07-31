#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "battleship.h"
#include <assert.h>

static void readMessage(int fd, int *msg) {
   if (sizeof(int) != read(fd, msg, sizeof(int)))
   {
      fprintf(stderr, "read failure in %s at line %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   }
   assert(*msg == NEW_GAME || *msg == SHOT_REQUEST || *msg == SHOT_RESULT || 
      *msg == OPPONENTS_SHOT || *msg == MATCH_OVER);
}

static void readStatus(int fd, int *status) {
   if (sizeof(int) != read(fd, status, sizeof(int)))
   {
      fprintf(stderr, "read failure in %s at line %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   }
   assert(*status == MISS || *status == HIT || *status == SINK);
}

static void readShot(int fd, Shot *shot) {
   if (sizeof(Shot) != read(fd, shot, sizeof(Shot))) {
      fprintf(stderr, "read failure in %s at line %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   }
}

static void writeBoard(int fd, char board[][SIZE]) {
   int i, j;
   
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         if (1 != write(fd, &board[i][j], 1)) {
            fprintf(stderr, "write failure in %s at line %d\n", __FILE__, 
               __LINE__);
            exit(EXIT_FAILURE);
         }
      }
   }
}

static void writeShot(int fd, Shot *shot) {
   if (sizeof(Shot) != write(fd, shot, sizeof(Shot))) {
      fprintf(stderr, "write failure in %s at line %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   }
}

static int getFD(const char *arg) {
   int fd;

   if (1 != sscanf(arg, "%d", &fd))
   {
      fprintf(stderr, "Bad fd argument\n");
      exit(EXIT_FAILURE);
   }

   return fd;
}

static void createNewShot(int totalShots, Shot *next) {
   if (totalShots == 0) {
      next->row = 0;
      next->col = 0;
   }
   else {
      next->col++;
      if (next->col == SIZE) {
         next->row++;
         next->col = 0;
      }
      else if (next->row == SIZE) {
         next->row = 0;
      }
   }
}

static void createBoard(char board[][SIZE]) {
   int i = 0, j = 0;

   while (i < SIZE) {
      while (j < SIZE) {
         board[i][j] = OPEN_WATER;
         j++;
      }
      i++;
      j = 0;
   }

   board[1][4] = PATROL_BOAT;
   board[1][5] = PATROL_BOAT;
   board[2][3] = DESTROYER;  
   board[3][3] = DESTROYER;  
   board[4][3] = DESTROYER;  
   board[4][0] = SUBMARINE;
   board[5][0] = SUBMARINE;
   board[6][0] = SUBMARINE;
   board[6][5] = AIRCRAFT_CARRIER;
   board[6][6] = AIRCRAFT_CARRIER;
   board[6][7] = AIRCRAFT_CARRIER;
   board[6][8] = AIRCRAFT_CARRIER;
   board[6][9] = AIRCRAFT_CARRIER;
   board[9][1] = BATTLESHIP;
   board[9][2] = BATTLESHIP;
   board[9][3] = BATTLESHIP;
   board[9][4] = BATTLESHIP;
}

static void determineStatus(int inMsg, char board[][SIZE], Shot *newShot, 
   int *totalShots, int readFD, int writeFD) {
   int status = 0;
   Shot temp;

   if (inMsg == NEW_GAME) {
      *totalShots = 0;
      writeBoard(writeFD, board);
   }
   else if (inMsg == SHOT_REQUEST) {
      createNewShot(*totalShots, newShot);
      (*totalShots)++;
      writeShot(writeFD, newShot);
   }
   else if (inMsg == SHOT_RESULT) {
      readStatus(readFD, &status); 
   }
   else if (inMsg == OPPONENTS_SHOT) {
      readShot(readFD, &temp);   
   }
   else {
      fprintf(stderr, "Invalid Host Command\n");
      exit(EXIT_FAILURE);
   }
}

int main(int argc, char **argv)
{
   Shot newShot;
   int readFD, writeFD, inMsg, totalShots = 0;
   char board[SIZE][SIZE];

   if (argc != 3)
   {
      fprintf(stderr, "Usage: player readFD writeFD\n");
      exit(EXIT_FAILURE);
   }

   readFD = getFD(argv[1]);
   writeFD = getFD(argv[2]);
  
   createBoard(board);
   while(totalShots < MAX_SHOTS) {
      readMessage(readFD, &inMsg);

      if (inMsg == MATCH_OVER) 
         break;
      determineStatus(inMsg, board, &newShot, &totalShots, readFD, writeFD); 
   }

   return EXIT_SUCCESS;
}
