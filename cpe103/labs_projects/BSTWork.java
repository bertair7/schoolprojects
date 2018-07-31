import java.util.Scanner;
public class BSTWork {

   public static void main(String args[]) { //tests out the heap class
   
      Scanner in = new Scanner(System.in);
      BasicBST test = new BasicBST(); 
      boolean isDone = false;

      System.out.println("Choose one of the following operations:");
      System.out.println("- insert an element (enter the letter a)");
      System.out.println("- find number of odds (enter the letter o)");
      System.out.println("- height of tree (enter the letter h)");
      System.out.println("- find number of leaves (enter the letter l)");
      System.out.println("- find number of one-child parents (enter the letter c)");
      System.out.println("- Quit (enter the letter q)");


      while(!isDone) { //checking to see when done
         String str = in.nextLine();
         switch(str) {
            case "a": //insert method
               System.out.print("Please input a number to add: ");
               int val = in.nextInt();
               test.insert(val);
               System.out.println(val + " inserted");
               in.nextLine();
               break;

            case "o": 
               System.out.println("There are " + test.countOdds() + " number of odds");
	       break;            

            case "h": 
	       System.out.println("The height of the tree is: " + test.height());
	       break;
	             
            case "l": 
	       System.out.println("The number of leaves is: " + test.countLeaves());
	       break;   
	           
            case "c": 
	       System.out.println("The number of one-child parents is: " + test.countOneChildParents());
	       break;                  

            case "q": //quit method
               System.out.println("Quitting");
               in.close();
	       isDone = true;
               System.out.println();
               break;
            
            default:
               System.out.println("Invalid choice");
               break;
         }
      }
   
   }

}
