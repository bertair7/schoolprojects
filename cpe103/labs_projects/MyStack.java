/*  Ryan Blair and Garrett Leone
*   rablair	   gcleone
*   Date: 11/3/15 
*   Project 3
*/


import java.util.EmptyStackException;

public class MyStack <T> {

   private Node top;

   private class Node {
      public T value;
      public Node next;
   }

   public MyStack() {
      top = null;
   }

   public void push(T item) {
      Node nextItem = new Node();
      nextItem.value = item;
      nextItem.next = top;
      top = nextItem;
   }

   public T pop() {
      if( !isEmpty() ) {
         T popper = top.value;
         top = top.next;
         return popper;
      }
      else throw new EmptyStackException();
   }

   public T peek() {
      if( !isEmpty() ) {
         T peeker = top.value;
         return peeker;
      }
      else throw new EmptyStackException();
   }

   public boolean isEmpty() {
      return top == null;
   }
}
