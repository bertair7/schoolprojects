/* Ryan Blair
 * Brandon Wilson
 * 1/9/17
 * Lab 0
 */

public class Algorithms {
   public static void linearAlgorithm(long N) {
      long i;
      int x;

      for (i = 0; i < N; i++) {
         x = 1;
      }
   }

   public static void quadraticAlgorithm(long N) {
      long i, j;
      int x;

      for (i = 0; i < N; i++) {
         for (j = 0; j < N; j++) 
            x = 1;
      }
   }

   public static void cubicAlgorithm(long N) {
      long i, j, k;
      int x;

      for (i = 0; i < N; i++) {
         for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++)
               x = 1;
         }
      }
   }

   public static void logarithmicAlgorithm(long N) {
      long i;
      int x; 

      for (i = N; i > 1; i = i/2) {
         x = 1;
      }
   }

   public static void NlogNAlgorithm(long N) {
      long i, j;
      int x;
      for (i = 0; i < N; i++) {
         for (j = N; j > 1; j = j/2) 
            x = 1;
      }
   }
   
}
