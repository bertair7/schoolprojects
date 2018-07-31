import java.util.Scanner;
import java.lang.RuntimeException;

public class LQueueDriver
{
   public static void main(String[] args) {
      Scanner in = new Scanner(System.in);
      LQueue<Integer> test = new LQueue<Integer>();

      System.out.println("Choose one of the following operations");
      System.out.println("- enqueue/add (enter the letter a)");
      System.out.println("- dequeue/delete (enter the letter d)");
      System.out.println("- check if the list is empty (enter the letter e)");
      System.out.println("- quit (enter the letter q)");

      while(in.hasNext()) {
         String str = in.nextLine();
         if(str.equals("a")) {
            //in.nextLine();
            System.out.print("Input an integer: ");
            if(in.hasNextInt()) {
               int temp = in.nextInt();
               test.enqueue(temp);
               System.out.println(temp + " enqueued");
               in.nextLine();
            }
            else {
               System.out.println("Invalid input");
               in.nextLine();
            }
         }
         else if(str.equals("d")) {
            //in.nextLine();
            try {
               int out = test.dequeue();
               System.out.println(out + " dequeued");
            }
            catch(LQueue.MyException exc) {
               System.out.print("Invalid operation/");
               System.out.println(exc.getMessage());
            }
         }
         else if(str.equals("e")) {
            //in.nextLine();
            if(test.isEmpty()) 
               System.out.println("Empty");
            else
               System.out.println("Not empty");
         }
         else if(str.equals("q")) {
            System.out.println("Quitting");
            in.close();
            while(!test.isEmpty()) {
               int list = test.dequeue();
               System.out.print(list + " ");
            }
            System.out.println();
            break;
         }
         else {
            System.out.println("Invalid operation");
         }
      }
   }
   
}
