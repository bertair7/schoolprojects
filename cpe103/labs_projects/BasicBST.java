import java.lang.*;
public class BasicBST {

   private class BSTNode {
      BSTNode right;
      BSTNode left;   
      int element;
   }

   private BSTNode root;
   
   public BasicBST() {
      root = null;
   }

   public void insert(int item) {
      root = insert(item, root);   
   }

   private BSTNode insert(int item, BSTNode root) {
      if(root == null) {
         BSTNode newNode = new BSTNode();
         root = newNode;
         newNode.element = item;
      } 

      else {
         if(item < root.element)
            root.left = insert(item, root.left);
         else
            root.right = insert(item, root.right);
      }
      return root;
   }

   public int countOdds() {
      return countOdds(root);
   }

   private int countOdds(BSTNode root) {
      int odds = 0;
      if(root == null)         
         return 0;
      else {
         if(root.element % 2 == 1)
            odds = 1 + countOdds(root.left) + countOdds(root.right);
         else
            odds = countOdds(root.left) + countOdds(root.right);
      }
      return odds;
   }

   public int height() {
      return height(root);
   }

   private int height(BSTNode root) {
      if(root == null) 
	 return -1;
      else 
      	 return 1 + Math.max(height(root.left), height(root.right));
   }

   public int countLeaves() {
      return countLeaves(root);
   }

   private int countLeaves(BSTNode root) {
      if(root == null) 
         return 0;
      else {
	 if(root.left != null || root.right != null) 
            return countLeaves(root.left) + countLeaves(root.right);
 	 else
	    return 1;
      }
   }

   public int countOneChildParents() {
      return countOneChildParents(root);
   }

   private int countOneChildParents(BSTNode root) {
      int oneParents = 0;
      if(root == null) 
         return 0;
      else {
	 if(root.right == null) {	//right is null
	    if(root.left != null)	//left is valid, right is null
	       oneParents = countOneChildParents(root.left) + 1;
 	 }
         else {				//right is valid
 	    if(root.left == null) 	//left is null, right is valid
	       oneParents = countOneChildParents(root.right) + 1;
            else 			//right is valid, left is valid
	       oneParents = countOneChildParents(root.right) + countOneChildParents(root.left);
         }
      }
      return oneParents;
   }
}
