// Ryan Blair rablair
// Ruslan Adamovics radamovi
// Project 3 Pt 1
// 2/15/17

import java.util.*;
import java.io.*;

public class FactoryProblem {

   private static class Route {
      int[] route;
      int totCost;
   }

   private static int[] findRoute(int[] l1, int[] l2, int L, int n) {
      int[] route = new int[n];
      int x = L;

      for (int i = n-1; i >= 0; i--) {
         if (x == 1) {
            route[i] = 1;
            x = l1[i];
         }
         else {
            route[i] = 2;
            x = l2[i];
         }
      }

      return route;
   }

   public static Route fastestRoute(int n, int e1, int e2, int x1, int x2, 
      int[] A1, int[] A2, int[] T1, int[] T2, Route r) {
      r.route = new int[n];
      int[] f1 = new int[n];
      int[] f2 = new int[n];
      int[] l1 = new int[n];
      int[] l2 = new int[n];
      int j, t, F, L;

      f1[0] = e1+A1[0];
      f2[0] = e2+A2[0];

      for (j = 1; j < n; j++) {
         int val1 = f1[j-1] + A1[j];
         int val2 = f2[j-1] + T2[j-1] + A1[j];

         l1[j] = Min(val1, val2);
         if(l1[j] == 1)
            f1[j] = val1;
         else
            f1[j] = val2;

         int val3 = f2[j-1] + A2[j];
         int val4 = f1[j-1] + T1[j-1] + A2[j];

         l2[j] = Min(val4, val3);
         if(l2[j] == 1)
            f2[j] = val4;
         else
            f2[j] = val3;
      }

      int F1 = f1[j-1] + x1;
      int F2 = f2[j-1] + x2;

      if(F1 < F2) {
         r.totCost = F1;
         L = 1;
      }
      else {
         r.totCost = F2;
         L = 2;
      }

      r.route = findRoute(l1, l2, L, n);

      return r;
   }

   private static int Min(int x, int y) {
      if (x < y)
         return 1;
      return 2;
   }

   public static void main(String[] args) throws IOException {
      System.out.format("Enter a file name: ");
      Scanner s = new Scanner(System.in);
      File input = new File(s.nextLine());
      Scanner in = new Scanner(input);

      int n = in.nextInt();
      int e1 = in.nextInt();
      int e2 = in.nextInt();

      int x1 = in.nextInt();
      int x2 = in.nextInt();

      int[] A1 = new int[n];
      for (int x = 0; x < n; x++){
         A1[x] = in.nextInt();
      }
      int[] A2 = new int[n];
      for (int x = 0; x < n; x++){
         A2[x] = in.nextInt();
      }

      int[] T1 = new int[n];
      for (int x = 0; x < n-1; x++){
         T1[x] = in.nextInt();
      }
      int[] T2 = new int[n];
      for (int x = 0; x < n-1; x++){
         T2[x] = in.nextInt();
      }

      Route r = new Route();
      r = fastestRoute(n, e1, e2, x1, x2, A1, A2, T1, T2, r);

      System.out.format("Fastest time is: %d\n\n", r.totCost);
      System.out.format("The optimal route is:\n");
      for (int x = 0; x < n; x++) {
         System.out.format("station %d, line %d\n", x+1, r.route[x]);
      }
   }

}
