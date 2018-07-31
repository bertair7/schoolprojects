import java.lang.RuntimeException;

public class AStack <T> {

   private T[] arr;
   private int top;

   public AStack(int size) {
      arr = (T[]) new Object[size];
      top = -1;
   }

   public static class MyException extends RuntimeException {
      public MyException() 
      {  super();   }
      public MyException(String message) 
      {  super(message);  }
   }

   public void push(T item) {
      if(top < arr.length-1) {
         top++;
         arr[top] = item;
      }
      else {
         int newSize = arr.length * 2;
         T[] temp = (T[]) new Object[newSize];
         
         for(int i = 0; i < arr.length; i++) {
            temp[i] = arr[i];
         } 
         arr = temp;
     
         top++;
         arr[top] = item;
      }
   }

   public T pop() {
      if( !isEmpty() ) {
         T popper = arr[top];
         top--;
         return popper;
      }
      else throw new MyException("Stack is empty");
   }

   public T peek() {
      if( !isEmpty() ) {
         T peeker = arr[top];
         return peeker;
      }
      else throw new MyException("Stack is empty");
   }

   public boolean isEmpty() {
      if(top == -1)
         return true;
      return false;
   }
}