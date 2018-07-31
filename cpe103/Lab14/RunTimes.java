
public class RunTimes {

   public static void main(String[] args) {

      //log
      System.out.println("Logarithmic algorithm's running times:");
      
      for(long i = 10000; i < 100000000; i = 2*i) {
         long startTime = System.nanoTime();
         Algorithms.logarithmicAlgorithm(i);
         long endTime = System.nanoTime();
         long total = (endTime - startTime) / 1000000;
         System.out.println("T(" + i + ") = " + total);
      }

      //linear
      System.out.println("Linear algorithm's running times:");
      for(long i = 10000; i < 100000000; i = 2*i) {
         long startTime = System.nanoTime();
         Algorithms.linearAlgorithm(i);
         long endTime = System.nanoTime();
         long total = (endTime - startTime) / 1000000;
         System.out.println("T(" + i + ") = " + total);
      }

      //NlogN
      System.out.println("NlogN algorithm's running times:");
      for(long i = 10000; i < 100000000; i = 2*i) {
         long startTime = System.nanoTime();
         Algorithms.NlogNAlgorithm(i);
         long endTime = System.nanoTime();
         long total = (endTime - startTime) / 1000000;
         System.out.println("T(" + i + ") = " + total);
      }
 
      //quadratic
      System.out.println("Quadratic algorithm's running times:");
      for(long i = 10000; i < 800000; i = 2*i) {
         long startTime = System.nanoTime();
         Algorithms.quadraticAlgorithm(i);
         long endTime = System.nanoTime();
         long total = (endTime - startTime) / 1000000;
         System.out.println("T(" + i + ") = " + total);
      }

   }
}
