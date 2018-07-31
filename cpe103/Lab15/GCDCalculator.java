import java.util.*;
import java.lang.*;
public class GCDCalculator {
   //Precondition: x, y > 0
   public static int gcd(int one, int two) {
      return greatestCommonDivisor(one, two);
   }

   private static int greatestCommonDivisor(int one, int two) {
      if(one == two) 
         return one;
      else {
         if(one > two) 
            return gcd(one - two, two);
         else
            return gcd(one, two - one);
      }
   }

   public static void main(String[] args) {
      int first;
      int second;
      String choice = "";
      Scanner in = new Scanner(System.in);
 
      while(!choice.equals("N")) {
         System.out.print("Enter 2 integers: ");
         first = in.nextInt();
         second = in.nextInt();

         System.out.println("Greatest Common Divisor = " + gcd(first, second));

         System.out.print("Continue? Y/N ");
         choice = in.next();
      }
   }
}
