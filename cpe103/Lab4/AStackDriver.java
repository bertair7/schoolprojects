import java.lang.RuntimeException;
import java.util.Scanner;

public class AStackDriver {

   public static void main(String[] args) {
      Scanner in = new Scanner(System.in);
      AStack<Integer> test = new AStack<Integer>(5);
      boolean isDone = false;

      System.out.println("Choose one of the following operations");
      System.out.println("- add/push (enter the letter a)");
      System.out.println("- delete/pop (enter the letter d)");
      System.out.println("- peek (enter the letter p)");
      System.out.println("- check if the list is empty (enter the letter e)");
      System.out.println("- quit (enter the letter q)");

      while(!isDone) {
         String str = in.nextLine();
         switch(str) {
            case "a": 
               System.out.print("Input an integer: ");
               if(in.hasNextInt()) {
                  int temp = in.nextInt();
                  test.push(temp);
                  System.out.println(temp + " pushed");
                  in.nextLine();
               }
               else {
                  System.out.println("Invalid input");
                  in.nextLine();
               }
               break;

            case "d": 
               try {
                  int out = test.pop();
                  System.out.println(out + " popped");
               }
               catch(AStack.MyException exc) {
                  System.out.print("Invalid operation/");
                  System.out.println(exc.getMessage());
               }
	       break;            

            case "e":
               if(test.isEmpty()) 
                  System.out.println("Empty");
               else
                  System.out.println("Not empty");
               break;

            case "p":
               try {
                  int out = test.peek();
                  System.out.println(out + " is at the top");
               }
               catch(AStack.MyException exc) {
                  System.out.print("Invalid operation/");
                  System.out.println(exc.getMessage());
               }
	       break;                     

            case "q": 
               System.out.println("Quitting");
               in.close();
               while(!test.isEmpty()) {
                  int list = test.pop();
                  System.out.print(list + " ");
               }
               System.out.println();
	       isDone = true;
               break;

            default: 
               System.out.println("Invalid operation");
               break;
         }
      }
   }

}
