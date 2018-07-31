import java.util.Scanner;
public class BSTWork {

   public static void main(String args[]) { //tests out the heap class
   
      Scanner in = new Scanner(System.in);
      BasicBST<Integer> test = new BasicBST<Integer>(); 
      boolean isDone = false;

      //menu
      System.out.println("Choose one of the following operations by entering the provided letter:");
      System.out.println("a - add the element");
      System.out.println("d - delete the element");
      System.out.println("f - find the element");
      System.out.println("e - check if the tree is empty");
      System.out.println("k - make the tree empty");
      System.out.println("n - get the number of nodes (the size) of the tree");
      System.out.println("m - find the minimal element");
      System.out.println("x - find the maximal element");
      System.out.println("p - print the tree in preorder using iterator");
      System.out.println("i - print the tree in inorder using iterator");
      System.out.println("l - print the tree in levelorder using iterator");
      System.out.println("t - print the tree using printTree");
      System.out.println("o - output the tree using toString");
      System.out.println("q - Quit the program");


      while(!isDone) { //checking to see when done
         String str = in.nextLine();
         switch(str) {
            case "a": //insert
               System.out.print("Please input a number to add: ");
               int val = in.nextInt();
               test.insert(val);
               System.out.println(val + " inserted");
               in.nextLine();
               break;

            case "d": //delete
               System.out.print("Please input a number to delete: ");
               int vald = in.nextInt();
               if(test.find(vald)) {
                  test.delete(vald);
                  System.out.println(vald + " deleted");
	       }
	       else 
		  System.out.println(vald + " is not in the tree");
               in.nextLine();	       
	       break;            

            case "f": //find
               System.out.print("Please input a number to find: ");
	       int valf = in.nextInt();
	       if(test.find(valf)) 
		  System.out.println(valf + " is in the tree");
	       else
		  System.out.println(valf + " is not in the tree");
	       in.nextLine();	       
	       break;
	             
            case "e": //check if empty
	       if(test.isEmpty())
		  System.out.println("The tree is empty");
	       else
		  System.out.println("The tree is not empty");
	       break;   
	           
            case "k": //make tree empty
	       test.makeEmpty();
	       System.out.println("The tree is now empty");
	       break;       
          
            case "n": //get size (# nodes)
	       int size = test.size();
	       System.out.println("The size of the tree is: " + size);
	       break;

            case "m": //find min
	       try {
		  int min = test.findMinimum();
		  System.out.println("The minimum element is: " + min);
	       }
	       catch (MyException e) 
	       	  System.out.println("The tree is empty/no minimum element");
	       break;

            case "x": //find max
	       try {
		  int max = test.findMaximum();
		  System.out.println("The maximum element is: " + max);
	       }
	       catch (MyException e) 
	       	  System.out.println("The tree is empty/no maximum element");
	       break;

            case "p": //print preorder
	       Iterator<Integer> iterPre = test.iteratorPre();
	       System.out.print("p - ");
	       while(iterPre.hasNext()) {	
		  System.out.print(iterPre.next() + " ");
	       System.out.println();
	       break;

            case "i": //print inorder
	       Iterator<Integer> iterIn = test.iteratorIn();
               System.out.print("i - ");
	       while(iterIn.hasNext()) {
		  System.out.print(iterIn.next() + " ");
	       System.out.println();
	       break;

            case "l": //print levelorder
	       Iterator<Integer> iterLevel = test.iteratorLevel();
               System.out.print("l - ");
	       while(iterLevel.hasNext()) {
		  System.out.print(iterLevel.next() + " ");
	       System.out.println();
	       break;

            case "t": //printTree
	       test.printTree();
	       break;

            case "o": //toString
	       System.out.println(test.toString());
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
