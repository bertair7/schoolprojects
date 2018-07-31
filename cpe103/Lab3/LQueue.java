import java.lang.RuntimeException;

public class LQueue <T>
{
   private class Node {
      public T value;
      public Node next;
   }

   public static class MyException extends RuntimeException {
      public MyException() 
      {  super();   }
      public MyException(String message) 
      {  super(message);  }
   }

   private Node front;
   private Node end;

   public LQueue () {  front = end = null;  }

   public void enqueue(T item) {
      Node input = new Node();
      input.value = item;

      if( !isEmpty() )           //queue not empty
         end.next = input;  
      else                      //queue empty
         front = input;

      end = input;   
   }

   public T dequeue() {
      if( !isEmpty() ) {
         T temp = front.value;
         front = front.next;
         return temp;
      }
      else throw new MyException("Queue is empty");
   }

   public boolean isEmpty() {
      if(front == null)
         return true;
      return false;
   }
}
