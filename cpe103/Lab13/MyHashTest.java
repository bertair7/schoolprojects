import java.util.*;

public class MyHashTest {
   public static void main(String args[]) { 
   
      Scanner in = new Scanner(System.in);
      MyHashTable<Integer> test = new MyHashTable<Integer>(10); 
      boolean isDone = false;

      System.out.println("Choose one of the following operations:");
      System.out.println("- add (a)");
      System.out.println("- find (f)");
      System.out.println("- delete (d)");
      System.out.println("- is empty (e)");
      System.out.println("- print (p)");
      System.out.println("- make empty (k)");
      System.out.println("- size (s)");
      System.out.println("- output the collection (o)");
      System.out.println("- quit (q)");


      while(!isDone) { 
         String str = in.nextLine();
         switch(str) {
            case "a": //add method
               System.out.print("Please input a number to add: ");
               int val = in.nextInt();
               test.insert(val);
               System.out.println(val + " inserted");
	       in.nextLine();
               break;
             
            case "f": //find method
	       System.out.print("Please input a number to find: ");
               int valf = in.nextInt();
               if(test.find(valf))
		  System.out.println(valf + " is in the Hash table");
	       else
		  System.out.println(valf + " is not in the Hash table");
	       in.nextLine();
               break;  

            case "d": //delete method
	       System.out.print("Please input a number to delete: ");
               int vald = in.nextInt();
               test.delete(vald);
               System.out.println(vald + " deleted");
	       in.nextLine();
	       break;            

            case "e": //isEmpty method
	       if(test.isEmpty())
		  System.out.println("The hash table is empty");
	       else
		  System.out.println("The hash table is not empty");
	       break;
            
            case "p": //print method
	       test.print();
	       break;      

            case "k": //make empty method
	       test.makeEmpty();
	       System.out.println("The hash table is now empty");
	       break; 

            case "s": //size method
	       System.out.println("The size is: " + test.size());
	       break; 

            case "o": //output method
	       Iterator<Integer> iter = test.iterator();
	       while(iter.hasNext()) 
                  System.out.print(iter.next() + " ");
               System.out.println();
	       break;             

            case "q": //quit method
               System.out.println("Quitting");
               in.close();
	       isDone = true;
               break;
            
            default:
               System.out.println("Invalid choice");
               break;
         }
      }
   
   }
}
