import java.util.Scanner;

public class AVLTest {

   public static void main(String[] args) {
      Scanner in = new Scanner(System.in);
      BasicAVL test = new BasicAVL();
      boolean isDone = false;

      System.out.println("Choose one of the following operations");
      System.out.println("- add/insert (a)");
      System.out.println("- print (p)");
      System.out.println("- quit (q)");

      while(!isDone) {
         String str = in.nextLine();
         switch(str) {
            case "a": 
	       System.out.print("Input an integer: ");
               int value = in.nextInt();
       	       test.insert(value);
	       in.nextLine();
               break;

            case "p":
               test.print();
	       break;                     

            case "q": 
               System.out.println("Quitting");
               in.close();
	       isDone = true;
               break;
         }
      }
   }
}