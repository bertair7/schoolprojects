import java.util.Scanner;

public class TreeTest {

   public static void main(String [] arg) {
      Integer[] tree = new Integer[20];
      int numValues = 0;
      Scanner in = new Scanner(System.in);
      System.out.println("Please input integers to add: ");

      while(in.hasNext() || (numValues < tree.length)) {
         int next = in.nextInt();
         tree[numValues] = next;
         numValues++;
      }
      if(numValues == 0) {
         System.out.println("The tree is empty");
      }
      else {
         boolean heap = TreeWork.isHeap(tree, numValues);
         if(heap) 
	    System.out.println("It is a heap");
      
         else 
            System.out.println("It is not a heap");
         TreeWork.printTree(tree, numValues);
      }
   }

}
