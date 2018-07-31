// Ryan Blair rablair
// Ruslan Adamovics radamovi
// Project 3 Pt 2
// 2/15/17

import java.io.*;
import java.lang.Math;
import java.util.*;

public class GameProblem {
   
   private static class Max {
      int max;
      int maxI;
      int maxJ;
   }

   private static char e = 'e';
   private static char r = 'r';
   private static char d = 'd';

   private static Max getMax(Max m, int val, int i, int j) {
      Max next = new Max();
      if (m.max < val) {
         next.max = val;
         next.maxI = i;
         next.maxJ = j;
         return next;
      }
      return m;
   }

   public static void game(int n, int m, int[][] A) {
      int[][] S = new int[n][m];
      char[][] R = new char[n][m];
      Max mx = new Max();
      mx.max = -1000;
      mx.maxI = 0;
      mx.maxJ = 0;

      for (int i = n-1; i >= 0; i--) {
         for (int j = m-1; j >= 0; j--) {
            if (i == n-1 && j == m-1) { // bottom-right corner
               S[i][j] = A[i][j];
               R[i][j] = e;
               mx = getMax(mx, S[i][j], i, j);
            }
            else if (j == m-1) { // right column
               if (S[i+1][j] > 0) {
                  S[i][j] = S[i+1][j] + A[i][j];
                  R[i][j] = d;
                  mx = getMax(mx, S[i][j], i, j);
               }
               else {
                  S[i][j] = A[i][j];
                  R[i][j] = e;
                  mx = getMax(mx, S[i][j], i, j);
               }
            }
            else if (i == n-1) { // bottom row
               if (S[i][j+1] > 0) {
                  S[i][j] = S[i][j+1] + A[i][j];
                  R[i][j] = r;
                  mx = getMax(mx, S[i][j], i, j);
               }
               else {
                  S[i][j] = A[i][j];
                  R[i][j] = e;
                  mx = getMax(mx, S[i][j], i, j);
               }
            }
            else { // anywhere else other than edges
               if (S[i][j+1] > S[i+1][j]) {
                  S[i][j] = S[i][j+1] + A[i][j];
                  R[i][j] = r;
                  mx = getMax(mx, S[i][j], i, j);
               }
               else {
                  S[i][j] = S[i+1][j] + A[i][j];
                  R[i][j] = d;
                  mx = getMax(mx, S[i][j], i, j);
               }
            }
         }
      }

      System.out.format("Best score: %d\n", mx.max);
      System.out.format("Best route: ");
      int x = mx.maxI;
      int y = mx.maxJ;
      char next = R[x][y];
      boolean t = true;

      while (t) {
         if (next != e) {
            System.out.format("[%d,%d] to ", x+1, y+1);
            if (next == r) {
               y++;
               next = R[x][y];
            }
            else {
               x++;
               next = R[x][y];
            }
         }
         else {
            System.out.format("[%d,%d] to exit\n", x+1, y+1);
            break;
         }   
      }
   }

   public static void main(String[] args) throws IOException {
      System.out.format("Enter a file name: ");
      Scanner s = new Scanner(System.in);
      File input = new File(s.nextLine());
      Scanner in = new Scanner(input);
      
      int n = in.nextInt();
      int m = in.nextInt();
      int[][] A = new int[n][m];

      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
            A[i][j] = in.nextInt(); 
         }
      }

      game(n, m, A);
   } 
}
