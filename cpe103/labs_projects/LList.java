import java.util.*;

public class LList<T> {

   private Node head;
   private class Node {
      T component;
      Node next;
   }

   public void add(T item) {
      Node object = new Node();
      object.component = item;
      if(head == null) {
         head = object;
      }
      else {
         Node current = head;
         while(current.next != null) {
            current = current.next;
         }
         current.next = object;
      }
   }

   public Iterator <T> iterator()
   {
      return new Iter();
   }

   private class Iter implements Iterator <T> {
      public Node cursor;
      public Iter() {
         cursor = head;
      }
      public boolean hasNext() {
         return cursor != null;
      }
      public T next() {
         if(!hasNext())
            throw new NoSuchElementException();
         T answer = cursor.component;
         cursor = cursor.next;
         return answer;
      }
      public void remove() {
         throw new UnsupportedOperationException();
      }

   }

}
