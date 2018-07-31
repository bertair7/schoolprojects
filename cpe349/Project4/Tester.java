// Ryan Blair rablair
// Ruslan Adamovics radamovi
// Project 4 
// 2/24/17

public class Tester {

   public static void main(String[] args) {
      System.out.format("Testing change_DP and change_greedy algorithms\n");
      
      int[] set1 = {100, 50, 25, 10, 5, 1};
      int[] set2 = {100, 50, 20, 15, 10, 5, 3, 2, 1};
      int[] set3 = {64, 32, 16, 8, 4, 2, 1};
      int[] set4 = {100, 50, 25, 10, 1};
      int[] set5 = {66, 35, 27, 18, 10, 1};

      int matches1 = 0;
      int matches2 = 0;
      int matches3 = 0;
      int matches4 = 0;
      int matches5 = 0;

      // Set 1
      for (int x = 1; x <= 200; x++) {
         int[] change1a = ChangeMaker.change_DP(x, set1);
         int[] change1b = ChangeMaker.change_greedy(x, set1);
         int coins1a = coinCount(change1a, set1.length);
         int coins1b = coinCount(change1b, set1.length);

         if (coins1a == coins1b)
            matches1++;
      }
      System.out.format("Testing set1: %d matches in 200 tests\n", matches1);
 
      // Set 2
      for (int x = 1; x <= 200; x++) {
         int[] change2a = ChangeMaker.change_DP(x, set2);
         int[] change2b = ChangeMaker.change_greedy(x, set2);
         int coins2a = coinCount(change2a, set2.length);
         int coins2b = coinCount(change2b, set2.length);

         if (coins2a == coins2b)
            matches2++;
      }
      System.out.format("Testing set2: %d matches in 200 tests\n", matches2);
      
      // Set 3
      for (int x = 1; x <= 200; x++) {
         int[] change3a = ChangeMaker.change_DP(x, set3);
         int[] change3b = ChangeMaker.change_greedy(x, set3);
         int coins3a = coinCount(change3a, set3.length);
         int coins3b = coinCount(change3b, set3.length);

         if (coins3a == coins3b)
            matches3++;
      }
      System.out.format("Testing set3: %d matches in 200 tests\n", matches3);
      
      // Set 4
      for (int x = 1; x <= 200; x++) {
         int[] change4a = ChangeMaker.change_DP(x, set4);
         int[] change4b = ChangeMaker.change_greedy(x, set4);
         int coins4a = coinCount(change4a, set4.length);
         int coins4b = coinCount(change4b, set4.length);

         if (coins4a == coins4b)
            matches4++;
      }
      System.out.format("Testing set4: %d matches in 200 tests\n", matches4);
      
      // Set 5
      for (int x = 1; x <= 200; x++) {
         int[] change5a = ChangeMaker.change_DP(x, set5);
         int[] change5b = ChangeMaker.change_greedy(x, set5);
         int coins5a = coinCount(change5a, set5.length);
         int coins5b = coinCount(change5b, set5.length);

         if (coins5a == coins5b)
            matches5++;
      }
      System.out.format("Testing set5: %d matches in 200 tests\n", matches5);
   }

   private static int coinCount(int[] change, int denoms) {
      int total = 0;

      for (int i = 0; i < denoms; i++) {
         if (change[i] > 0)
            total += change[i];
      }

      return total;
   }

}
