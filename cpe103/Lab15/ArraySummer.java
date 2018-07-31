import java.util.*;
public class ArraySummer {
   public static int arraySum(int[] array, int first) {
      return arraySumm(array, first);
   }

   private static int arraySumm(int[] array, int first) {
      if(first == (array.length - 1)) 
         return array[first];
      else 
         return array[first++] + arraySumm(array, first);
   }

   public static void main(String[] args) {
      int[] numbers = new int[10];
      Scanner in = new Scanner(System.in);

      System.out.print("Enter 10 integers: ");
      for(int i = 0; i < numbers.length; i++) {
         if(in.hasNextInt())
            numbers[i] = in.nextInt();
      }

      System.out.println("Total = " + arraySum(numbers, 0));
   }
}

