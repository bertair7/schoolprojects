import java.lang.System;
import java.io.*;

public class RunTimes {
   public static void displayResults(long start, long end, long N) {
      long total = end - start;
      total = total / 1000000;
      
      System.out.format("T(%d) = %d\n", N, total);
   }

   public static void main(String[] args) {
      long start, end;

      //print out running times statement
      System.out.format("Logarithmic algorithm's running times:\n");
      for (long N = 1000; N < 100000000; N = N*2) {
         start = System.nanoTime();
         Algorithms.logarithmicAlgorithm(N);
         end = System.nanoTime();
         displayResults(start, end, N);
      }

      System.out.format("Linear algorithm's running times:\n");
      for (long N = 1000; N < 100000000; N = N*2) {
         start = System.nanoTime();
         Algorithms.linearAlgorithm(N);
         end = System.nanoTime();
         displayResults(start, end, N);
      } 
  
      System.out.format("NlogN algorithm's running times:\n");
      for (long N = 1000; N < 100000000; N = N*2) {
         start = System.nanoTime();
         Algorithms.NlogNAlgorithm(N);
         end = System.nanoTime();
         displayResults(start, end, N);
      }   

      System.out.format("Quadratic algorithm's running times:\n");
      for (long N = 1000; N <= 512000; N = N*2) {
         start = System.nanoTime();
         Algorithms.quadraticAlgorithm(N);
         end = System.nanoTime();
         displayResults(start, end, N);
      } 
  
      System.out.format("Cubic algorithm's running times:\n");
      for (long N = 1000; N <= 8000; N = N*2) {
         start = System.nanoTime();
         Algorithms.cubicAlgorithm(N);
         end = System.nanoTime();
         displayResults(start, end, N);
      }   
   }
}

