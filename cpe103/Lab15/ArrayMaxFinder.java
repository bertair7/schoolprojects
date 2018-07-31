import java.util.*;
import java.lang.*;
public class ArrayMaxFinder {
   public static int arrayMax(int[] array, int first) {
      return arrayMaxx(array, first);
   }

   private static int arrayMaxx(int[] array, int first) {
      int max = 0;
      if(first == (array.length - 1)) 
         return array[first];
      else 
         max = Math.max(array[first++], arrayMaxx(array, first));
      return max;
   }

   public static void main(String[] args) {
      int[] numbers = new int[10];
      Scanner in = new Scanner(System.in);

      System.out.print("Enter 10 integers: ");
      for(int i = 0; i < numbers.length; i++) {
         if(in.hasNextInt())
            numbers[i] = in.nextInt();
      }

      System.out.println("Max = " + arrayMax(numbers, 0));
   }
}

