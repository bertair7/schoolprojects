/*  Ryan Blair and Garrett Leone
*   rablair	   gcleone
*   Date: 11/3/15 
*   Project 3
*/


import java.util.*;
import java.lang.*;
public class BST<T extends Comparable<? super T>> { 
 
   private class BSTNode { //Binary Search Tree nodes
      BSTNode right;
      BSTNode left;   
      T element;
   }

   private BSTNode root;
   
   private class PreIter implements Iterator<T> { //iterates through using preorder
      public BSTNode cursor;
      public MyStack<BSTNode> pre;

      public PreIter() {
         cursor = root;
         pre = new MyStack<BSTNode>();
         if(root != null) 
            pre.push(root);
      }

      public boolean hasNext() {
         return !pre.isEmpty();
      }

      public T next() {
         if(!hasNext())
            throw new NoSuchElementException();

         cursor = pre.pop();
         if(cursor.right != null)
            pre.push(cursor.right);
         if(cursor.left != null) 
            pre.push(cursor.left);
         return cursor.element;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }
   }
   
   private class InIter implements Iterator<T> { //iterates through using inorder
      public BSTNode cursor;
      public MyStack<BSTNode> in;

      public InIter() {
         cursor = root;
         in = new MyStack<BSTNode>();
	 if(root != null) {
	    in.push(root);
            stackUpLefts(root);
         }
      }

      public boolean hasNext() {
         return !in.isEmpty();
      }

      public T next() {
         if(!hasNext())
            throw new NoSuchElementException() 

          cursor = in.pop();
          if(cursor.right != null) { 
             in.push(cursor.right);
             stackUpLefts(cursor.right);
          }
          return cursor.element;    
      }   
   
      private void stackUpLefts(BSTNode x) {
         while(x.left != null) {
            in.push(x.left);
            x = x.left;
         }
      }    
 
      public void remove() {
         throw new UnsupportedOperationException();
      }
   }
   
   private class LevelIter implements Iterator<T> { //iterates through using levelorder
      public BSTNode cursor;
      public LQueue<BSTNode> level;

      public LevelIter() {
         cursor = root;
         level = new LQueue<BSTNode>();
	 if(root != null) 
            level.enqueue(root);
      }

      public boolean hasNext() {
         return !level.isEmpty();
      }

      public T next() {
         if(!hasNext())
            throw new NoSuchElementException();
         cursor = level.dequeue();
         if(cursor.left != null)
            level.enqueue(cursor.left);
         if(cursor.right != null)
            level.enqueue(cursor.right);
         return cursor.element;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }  

   }
   
   public static class MyException extends RuntimeException {
      public MyException() {
         super();
      }
      public MyException(String message) {
         super(message);
      }
   }

   public BST() { root = null; } //constructor

   public void insert(T item) {
      root = insert(item, root);
   }
   
   private BSTNode insert(T item, BSTNode treeroot) { 
      if(treeroot == null) { 
         BSTNode value = new BSTNode();
         treeroot = value;
         value.element = item;
      }
      else {
         if(item.compareTo(treeroot.element) < 0) 
            treeroot.left = insert(item, treeroot.left);
         else
            treeroot.right = insert(item, treeroot.right);
        }
      return treeroot;
   }

   public void delete(T item) {
      root = delete(item, root);
   }

   private BSTNode delete(T item, BSTNode treeroot) { 
      if(treeroot != null) { 
         if(item.compareTo(treeroot.element) < 0) 
            treeroot.left = delete(item, treeroot.left);
         else if(item.compareTo(treeroot.element) > 0)
            treeroot.right = delete(item, treeroot.right);
         else
            treeroot = deleteNode(treeroot);
      }
      return treeroot;
   }

   private BSTNode deleteNode(BSTNode x) { //helper method to delete nodes at the root
      BSTNode newRoot;
      if(x.left != null && x.right != null) {
         T nextValue = successor(x);
	 x.element = nextValue;
	 x.right = delete(nextValue, x.right);
	 newRoot = x;
      }
      else {
	 if(x.left != null) 
	    newRoot = x.left;
	 else {
	    if(x.right != null)
	       newRoot = x.right;
	    else
	       newRoot = null;
         }
      }
      return newRoot;
   }

   //Precondition: x != null && x has a right child
   private T successor(BSTNode x) {
      BSTNode temp = x.right;
      while(temp.left != null)
	 temp = temp.left;
      return temp.element;
   }

   public boolean find(T item) { //sees if item is in the tree
      return find(item, root);
   }

   private boolean find(T item, BSTNode treeroot) {
      boolean answer;
      if(treeroot == null)
         answer = false;
      else {
         if(item.compareTo(treeroot.element) == 0)
            answer = true;
         else {
            if(item.compareTo(treeroot.element) < 0) 
               answer = find(item, treeroot.left);
            else
               answer = find(item, treeroot.right);
         }
      }
      return answer;
   }

   public boolean isEmpty() {
      return (root == null);
   }

   public void makeEmpty() {
      root = null;
   }

   public int size() { //returns size of the tree
      return size(root);
   }
   
   private int size(BSTNode treeroot) {
      int answer;
      if(treeroot == null)
         answer = 0;
      else
         answer = size(treeroot.left) + 1 + size(treeroot.right);
      return answer;
   }
   
   public T findMinimum() {
      if(isEmpty())
         throw new MyException("Binary Search Tree is empty");
      else
         return findMinimum(root);
   }

   public T findMinimum(BSTNode treeroot) {
      BSTNode left = treeroot.left;
      T answer;
      if(left == null) 
         answer = treeroot.element;
      else
         answer = findMinimum(left);
      return answer;
    
   }

   public T findMaximum() {
      if(isEmpty())
         throw new MyException("Binary Search Tree is empty");
      else
         return findMaximum(root);
   }
   
   private T findMaximum(BSTNode treeroot) {
      BSTNode right = treeroot.right;
      T answer;
      if(right == null) 
         answer = treeroot.element;
      else
         answer = findMaximum(right);
      return answer;
   }

   public Iterator<T> iteratorPre() {
      return new PreIter();
   }

   public Iterator<T> iteratorIn() {
      return new InIter();
   }

   public Iterator<T> iteratorLevel() {
      return new LevelIter();
   }
   
   public void printTree() {
      printTree(root, "");
   }

   private void printTree(BSTNode treeroot, String indent) { //prints tree as a BST
      if(treeroot != null) {
	 System.out.println(indent + treeroot.element);
	 indent += "    ";
	 printTree(treeroot.left, indent);
	 printTree(treeroot.right, indent);
      }
   }
   
   public String toString() {
      return toString(root);
   }

   private String toString(BSTNode treeroot) {
      String result = "";
      if(treeroot != null) {
 	 result += treeroot.element + " ";
	 result += toString(treeroot.left);
	 result += toString(treeroot.right);
      }
      return result;
   }

}
