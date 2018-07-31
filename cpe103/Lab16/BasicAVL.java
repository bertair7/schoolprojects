
public class BasicAVL {
   private class AVLNode {
      int element;
      int height;
      AVLNode left;
      AVLNode right;
   }

   private AVLNode root;
  
   public BasicAVL() {
      root = null;
   }

   public void insert(int item) {
      root = insert(item, root);
   }

   private AVLNode insert(int item, AVLNode treeroot) {
      if(treeroot == null) {
         treeroot = new AVLNode();
	 treeroot.element = item;
      }
      else {
         if(item < treeroot.element) {
            treeroot.left = insert(item, treeroot.left);
	    if(treeroot.left.height - height(treeroot.right) == 2) {
	       if(item < treeroot.left.element)
		  treeroot = rotateWithLeft(treeroot);
	       else
		  treeroot = doubleLeftRight(treeroot);
	    }
	 }
	 else if(item > treeroot.element) {
	    treeroot.right = insert(item, treeroot.right);
	    if(treeroot.right.height - height(treeroot.left) == 2) {
	       if(item > treeroot.right.element)
		  treeroot = rotateWithRight(treeroot);
	       else
		  treeroot = doubleRightLeft(treeroot);
	    }
	 }
      }
      treeroot.height = Math.max(height(treeroot.left), height(treeroot.right)) + 1;
      return treeroot;
   }

   public void print() {
      print(root, "");
   }

   private void print(AVLNode treeroot, String tab) {
      if(treeroot != null) {
	 System.out.println(tab + treeroot.element);
	 tab += "    ";
	 print(treeroot.left, tab);
	 print(treeroot.right, tab);
      }
   }

   private int height(AVLNode node) {
      int answer;
      if(node != null)
	 answer = node.height;
      else
	 answer = -1;
      return answer;
   }

   private AVLNode rotateWithLeft(AVLNode x) {
      AVLNode y = x.left;
      x.left = y.right;
      y.right = x;
      x.height = 1 + Math.max(height(x.right), height(x.left));
      y.height = 1 + Math.max(height(y.right), height(y.left));
      return y;
   }

   private AVLNode rotateWithRight(AVLNode x) {
      AVLNode y = x.right;
      x.right = y.left;
      y.left = x;
      x.height = 1 + Math.max(height(x.right), height(x.left));
      y.height = 1 + Math.max(height(y.right), height(y.left));
      return y;
   }

   private AVLNode doubleLeftRight(AVLNode x) {
      x.left = rotateWithRight(x.left);
      return rotateWithLeft(x);
   }

   private AVLNode doubleRightLeft(AVLNode x) {
      x.right = rotateWithLeft(x.right);
      return rotateWithRight(x);
   }
}
