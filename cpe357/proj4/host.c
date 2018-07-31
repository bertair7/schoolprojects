#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "battleship.h"

typedef struct {
   int health;
   int ifSunk;
} Ship;

typedef struct {
   char board[SIZE][SIZE];
   char playerName[20];
   int htp;
   int pth;
   Shot previous[MAX_SHOTS];
   int oppShot;
   int numShot;
   int numHits;
   int numMiss;
   int numSunk;
   int wins;
   int draws;
   int losses;
   Ship air;
   Ship battle;
   Ship destroy;
   Ship sub;
   Ship patrol;
} PlayerBoard;

static void initShips(PlayerBoard *p1, PlayerBoard *p2) {
   int i;
   Shot temp;
 
   p1->air.health = SIZE_AIRCRAFT_CARRIER;
   p1->air.ifSunk = 0;
   p1->battle.health = SIZE_BATTLESHIP;
   p1->battle.ifSunk = 0;
   p1->destroy.health = SIZE_DESTROYER;
   p1->destroy.ifSunk = 0;
   p1->sub.health = SIZE_SUBMARINE;
   p1->sub.ifSunk = 0;
   p1->patrol.health = SIZE_PATROL_BOAT;
   p1->patrol.ifSunk = 0;

   p2->air.health = SIZE_AIRCRAFT_CARRIER;
   p2->air.ifSunk = 0;
   p2->battle.health = SIZE_BATTLESHIP;
   p2->battle.ifSunk = 0;
   p2->destroy.health = SIZE_DESTROYER;
   p2->destroy.ifSunk = 0;
   p2->sub.health = SIZE_SUBMARINE;
   p2->sub.ifSunk = 0;
   p2->patrol.health = SIZE_PATROL_BOAT;
   p2->patrol.ifSunk = 0;

   temp.row = -1;
   temp.col = -1;
   for (i = 0; i < MAX_SHOTS; i++) {
      p1->previous[i] = temp;
      p2->previous[i] = temp;
   }
}

static void placeStr(char *player, char *arg) {
   char *temp, temp2[60];

   if (arg[0] == '/') {
      temp = strtok(arg, "/");
      while (temp != NULL) {
         strcpy(temp2, temp); 
         temp = strtok(NULL, "/");
      }
      strcpy(player, temp2);
   }
   else {
      strcpy(player, arg);
   }
}

static void initPlayers(PlayerBoard *p1, PlayerBoard *p2, char *p1name, 
   char *p2name, int hp1[2], int hp2[2], int p1h[2], int p2h[2]) {
   
   strcpy(p1->playerName, p1name);
   strcpy(p2->playerName, p2name);

   p1->htp = hp1[1];
   p1->pth = p1h[0];
   p1->oppShot = 0;
   p1->numShot = 0;
   p1->numHits = 0;
   p1->numMiss = 0;
   p1->numSunk = 0;
   p1->wins = 0;
   p1->draws = 0;
   p1->losses = 0;

   p2->htp = hp2[1];
   p2->pth = p2h[0];
   p2->oppShot = 0;
   p2->numShot = 0;
   p2->numHits = 0;
   p2->numMiss = 0;
   p2->numSunk = 0;
   p2->wins = 0;
   p2->draws = 0;
   p2->losses = 0;

   initShips(p1, p2);
}

static void createPipes(int hp1[2], int hp2[2], int p1h[2], int p2h[2]) {
   if (pipe(hp1) == -1) {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   if (pipe(p1h) == -1) {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   if (pipe(hp2) == -1) {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   if (pipe(p2h) == -1) {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
}

static void checkArgs(int argc, char **argv, int *numGames, int *dFlag, 
   char *player1, char *player2) {
   int i, players = 0;

   if (argc < 3 || argc > 6) {
      fprintf(stderr, "Usage: battleship [-gN|-d] player1 player2\n");
      exit(EXIT_FAILURE);
   }
    
   for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
         if (argv[i][1] == 'd')
            dFlag[0] = 1;
         else if (argv[i][1] == 'g' && argv[i][2] > 0)
            numGames[0] = atoi(&argv[i][2]);
         else {
            fprintf(stderr, "Usage: battleship [-gN|-d] player1 player2\n");
            exit(EXIT_FAILURE);
         }
      }
      else {
         if (players == 0) {
            strcpy(player1, argv[i]);
            players++;
         }
         else if (players == 1) {
            strcpy(player2, argv[i]);
            players++;
         }
         else {
            fprintf(stderr, "Usage: battleship [-gN|-d] player1 player2\n");
            exit(EXIT_FAILURE);
         }
      }
   }
}

static void writeMessage(int fd, int *msg) {
   if (sizeof(int) != write(fd, msg, sizeof(int))) {
      fprintf(stderr, "write failure in %s at line %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   }
}

static void writeShot(int fd, Shot *shot) {
   if (sizeof(Shot) != write(fd, shot, sizeof(Shot))) {
      fprintf(stderr, "write failure in %s at line %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   }
}

static void readBoard(int fd, char board[][SIZE]) {
   int i, j;
   
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         if (1 != read(fd, &board[i][j], 1)) {
            fprintf(stderr, "read failure in %s at line %d\n", __FILE__, 
               __LINE__);
            exit(EXIT_FAILURE);
         } 
      }
   }
}

static void readShot(int fd, Shot *shot) {
   if (sizeof(Shot) != read(fd, shot, sizeof(Shot))) {
      fprintf(stderr, "read failure in %s at line %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   } 
}

static int determineSink(char ship, Shot shot, PlayerBoard *p) {
   int sink = 0;

   if (ship == AIRCRAFT_CARRIER) {
      if (p->air.ifSunk == 1) {
         sink = 1;
         p->air.ifSunk = 2;
      }
   }
   else if (ship == BATTLESHIP) {
      if (p->battle.ifSunk == 1) {
         sink = 1;
         p->battle.ifSunk = 2;
      }
   }
   else if (ship == DESTROYER) {
      if (p->destroy.ifSunk == 1) {
         sink = 1;
         p->destroy.ifSunk = 2;
      }
   }
   else if (ship == SUBMARINE) {
      if (p->sub.ifSunk == 1) {
         sink = 1;
         p->sub.ifSunk = 2;
      }
   }
   else {
      if (p->patrol.ifSunk == 1) {
         sink = 1;
         p->patrol.ifSunk = 2;
      }
   }
   return sink;
}

static void updateShip(char ship, PlayerBoard *p) {
   if (ship == AIRCRAFT_CARRIER) {
      p->air.health--;
      if (p->air.health == 0)
         p->air.ifSunk = 1;
   }
   else if (ship == DESTROYER) {
      p->destroy.health--;
      if (p->destroy.health == 0)
         p->destroy.ifSunk = 1;
   }
   else if (ship == BATTLESHIP) {
      p->battle.health--;
      if (p->battle.health == 0)
         p->battle.ifSunk = 1;
   }
   else if (ship == SUBMARINE) {
      p->sub.health--;
      if (p->sub.health == 0)
         p->sub.ifSunk = 1;
   }
   else if (ship == PATROL_BOAT) {
      p->patrol.health--;
      if (p->patrol.health == 0)
         p->patrol.ifSunk = 1;
   }
}

static int determineShot(Shot shot, PlayerBoard *p) {
   int i, status = MISS, flag = 0;
   char ship;
   
   ship = p->board[shot.row][shot.col];
   if (ship != OPEN_WATER) {
      status = HIT;
      for (i = 0; i < MAX_SHOTS; i++) {
         if (shot.row == p->previous[i].row && 
            shot.col == p->previous[i].col) {
            flag = 1;
            break;
         }
      }
      if (!flag) {
         updateShip(ship, p);
         if (determineSink(ship, shot, p)) 
            status = SINK;
         p->previous[p->oppShot] = shot;
         p->oppShot++;
      }
   }

   return status;
}

static void displayMessage(int d, PlayerBoard *p, Shot shot, int shotStatus) {
   char *temp, miss[] = "Miss", hit[] = "HIT!", sink[] = "SINK!"; 

   if (shotStatus == MISS)
      temp = miss;
   else if (shotStatus == HIT)
      temp = hit;
   else if (shotStatus == SINK)
      temp = sink;
   
   if (d) {
      printf("%16s: shot[%2d][%2d], %5s, ", p->playerName, shot.row, 
         shot.col, temp); 
      printf("shots:%3d, misses:%2d, hits:%2d, sunk:%d\n", p->numShot, 
         p->numMiss, p->numHits, p->numSunk);
   }   

}

static void updatePlayer(PlayerBoard *p, int shotStatus) {
   int result = SHOT_RESULT;

   p->numShot++;
   if (shotStatus == MISS) 
      p->numMiss++;
   else if (shotStatus == HIT) 
      p->numHits++;
   else if (shotStatus == SINK) {
      p->numSunk++;
      p->numHits++;
   }

   writeMessage(p->htp, &result);
   writeMessage(p->htp, &shotStatus);
}

static void printRound(PlayerBoard *p1, PlayerBoard *p2, int round) {
   printf("\nGame %d Results: ", round);

   if (p1->numSunk == NUMBER_OF_SHIPS && p2->numSunk != NUMBER_OF_SHIPS) {
      printf("%s won!\n", p1->playerName);
      p1->wins++;
      p2->losses++;
   }
   else if (p2->numSunk == NUMBER_OF_SHIPS && p1->numSunk != NUMBER_OF_SHIPS) {
      printf("%s won!\n", p2->playerName);
      p2->wins++;
      p1->losses++;
   }
   else if (p1->numShot == MAX_SHOTS) {
      printf("No winner within %d shots\n", MAX_SHOTS);
      p1->losses++;
      p2->losses++;
   }
   else {
      printf("Draw\n");
      p1->draws++;
      p2->draws++;
   }

   printf("%16s: %d shots, %d hits, and %d sinks\n", p1->playerName, 
      p1->numShot, p1->numHits, p1->numSunk);
   printf("%16s: %d shots, %d hits, and %d sinks\n", p2->playerName, 
      p2->numShot, p2->numHits, p2->numSunk);
}

static void playRound(PlayerBoard *p1, PlayerBoard *p2, int dFlag, int round) {
   Shot temp;
   int shotStatus, shotReq = SHOT_REQUEST, oppShot = OPPONENTS_SHOT;

   if (dFlag)
      printf("\nGame %d Details:\n", round);

   while (p1->numShot < MAX_SHOTS) {
      writeMessage(p1->htp, &shotReq);
      readShot(p1->pth, &temp);
      shotStatus = determineShot(temp, p2);
      updatePlayer(p1, shotStatus);
      writeMessage(p2->htp, &oppShot);
      writeShot(p2->htp, &temp);
      displayMessage(dFlag, p1, temp, shotStatus);

      writeMessage(p2->htp, &shotReq);
      readShot(p2->pth, &temp);
      shotStatus = determineShot(temp, p1);
      updatePlayer(p2, shotStatus);
      writeMessage(p1->htp, &oppShot);
      writeShot(p1->htp, &temp);
      displayMessage(dFlag, p2, temp, shotStatus);
 
      if (p1->numSunk == NUMBER_OF_SHIPS || p2->numSunk == NUMBER_OF_SHIPS) 
         break;
   }
}

static void printGameResult(PlayerBoard *p1, PlayerBoard *p2, int numGames) {
   printf("\nMatch Results: ");

   if (p1->wins > p2->wins)
      printf("%s won!\n", p1->playerName);
   else if (p2->wins > p1->wins)
      printf("%s won!\n", p2->playerName);
   else
      printf("No winner in %d games\n", numGames);

   printf("%16s: %d wins, %d draws, and %d losses\n", p1->playerName, 
      p1->wins, p1->draws, p1->losses);
   printf("%16s: %d wins, %d draws, and %d losses\n", p2->playerName, 
      p2->wins, p2->draws, p2->losses);
}

static void clearPlayer(PlayerBoard *p1, PlayerBoard *p2) {
   p1->oppShot = 0;
   p1->numShot = 0;
   p1->numHits = 0;
   p1->numMiss = 0;
   p1->numSunk = 0;
   
   p2->oppShot = 0;
   p2->numShot = 0;
   p2->numHits = 0;
   p2->numMiss = 0;
   p2->numSunk = 0;
 
   initShips(p1, p2);  
}

static void playBattleship(char *player1, char *player2, int numGames, 
   int dFlag, char *rd1, char *rd2, char *wd1, char *wd2, int hp1[2], 
   int hp2[2], int p1h[2], int p2h[2]) {

   int i, newGame = NEW_GAME, matchOver = MATCH_OVER;
   pid_t pid1, pid2;
   PlayerBoard p1, p2;
   
   initPlayers(&p1, &p2, player1, player2, hp1, hp2, p1h, p2h);
   
   pid1 = fork();

   if (pid1 < 0) {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if (pid1 == 0) {
      execl(player1, player1, rd1, wd1, (char *)0);
      perror(NULL);
      exit(EXIT_FAILURE);
   }

   pid2 = fork();

   if (pid2 < 0) {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if (pid2 == 0) {
      execl(player2, player2, rd2, wd2, (char *)0);
      perror(NULL);
      exit(EXIT_FAILURE);
   }

   placeStr(p1.playerName, player1);
   placeStr(p2.playerName, player2);

   for (i = 0; i < numGames; i++) {
      writeMessage(p1.htp, &newGame);
      readBoard(p1.pth, p1.board);
      writeMessage(p2.htp, &newGame);
      readBoard(p2.pth, p2.board);
      
      playRound(&p1, &p2, dFlag, i+1);
      if (dFlag)
         printRound(&p1, &p2, i+1);
      clearPlayer(&p1, &p2);
   }
   writeMessage(p1.htp, &matchOver);
   writeMessage(p2.htp, &matchOver);
   printGameResult(&p1, &p2, numGames);
   
   exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
   int hp1[2], hp2[2], p1h[2], p2h[2], numGames = 3, dFlag = 0;
   char player1[60], player2[60], rd1[2], rd2[2], wd1[2], wd2[3];

   createPipes(hp1, hp2, p1h, p2h);
   sprintf(rd1, "%d", hp1[0]);
   rd1[1] = 0;
   sprintf(rd2, "%d", hp2[0]);
   rd2[1] = 0;
   sprintf(wd1, "%d", p1h[1]);
   wd1[1] = 0;
   sprintf(wd2, "%d", p2h[1]);
   wd2[2] = 0;

   checkArgs(argc, argv, &numGames, &dFlag, player1, player2);
   playBattleship(player1, player2, numGames, dFlag, rd1, rd2, wd1, wd2, hp1, 
      hp2, p1h, p2h);  

   exit(EXIT_SUCCESS);
}
