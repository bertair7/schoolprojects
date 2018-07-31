// Ryan Blair rablair
// Ruslan Adamovics radamovi
// Project 4 
// 2/24/17

import java.io.*;
import java.util.*;
import java.lang.System;

public class ChangeMaker {

   public static int[] change_DP(int n, int[] d) {
      int[] C = new int[n+1];
      int[] A = new int[n+1];
      int[] change = new int[d.length];

      C[0] = 0;
      for (int j = 1; j < n+1; j++) {
         int min = Integer.MAX_VALUE;

         for (int i = 0; i < d.length; i++) {
            if (j >= d[i] && min > C[j-d[i]]) {
               min = C[j-d[i]];
               A[j] = d[i];
            }
         }
         C[j] = 1 + min;
      }
      
      for (int i = 0; i < d.length; i++) {
         change[i] = 0;
      }

      for (int x = n; x > 0; x -= A[x]) {
         int coin = A[x];
         for (int i = 0; i < d.length; i++) {
            if (coin == d[i]) {
               change[i] += 1;
               break;
            }
         }
      }

      return change;
   }

   // Precondition: d denominations are in decreasing order
   public static int[] change_greedy(int n, int[] d) {
      int change[] = new int[d.length];
      int j = n;
      int i = 0;

      for (int x = 0; x < d.length; x++) {
         change[x] = 0;
      }

      while (j != 0) {
         if (j >= d[i]) {
            j -= d[i];
            change[i]++;
         }
         else
            i++;
      }

      return change;
   }

   public static void main(String[] args) throws IOException {
      System.out.format("Enter the number of coin-denominations and the set of coin values:\n");
      Scanner s = new Scanner(System.in);
      int denoms = s.nextInt();

      int[] d = new int[denoms];
      for (int x = 0; x < denoms; x++) {
         d[x] = s.nextInt();
         if (x > 0 && d[x] > d[x-1]) {
            System.out.format("Invalid denominations\n");
            System.exit(1);
         }
      }

      boolean c = true;
      while (c) {
         System.out.format("\nEnter a positive amount to be changed (enter 0 to quit): ");
         int n = s.nextInt();
         if (n < 0)
            System.out.format("Invalid value\n");
         else if (n == 0)
            c = false;
         else {
            int[] change = change_DP(n, d);
            System.out.format("\nDP algorithm results");
            printResults(change, d, n, denoms);

            int[] change2 = change_greedy(n, d);
            System.out.format("\nGreedy algorithm results");
            printResults(change2, d, n, denoms);
         }
      }
      System.out.format("Thanks for playing. Good Bye.\n");
   }

   public static void printResults(int[] change, int[] d, int n, int denoms) {
      System.out.format("\nAmount: %d", n);
      System.out.format("\nOptimal distribution: ");
        
      int total = 0;
      for (int x = 0; x < denoms; x++) {
         if (change[x] > 0  && total == 0) 
            System.out.format("%d*%dc", change[x], d[x]);
         else if (change[x] > 0) 
            System.out.format(" + %d*%dc", change[x], d[x]);

         total += change[x];
      }
      System.out.format("\nOptimal coin count: %d\n", total);
   } 
}
