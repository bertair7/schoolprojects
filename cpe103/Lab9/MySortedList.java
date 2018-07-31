
public class MySortedList {

   private class Node {
      int value;
      Node next;
   }

   private Node head;

   public MySortedList() {
      head = null;
   }

   public void add(int a) {
      if(isEmpty()) {
	 Node first = new Node();
         first.value = a;
         first.next = head;
         head = first;
      }
      else {
         Node newNode = new Node();
    	 newNode.value = a;

         Node current = head;
         Node previous = current;
         while((current != null) && (a > current.value)) {
	    previous = current;
            current = current.next;	    
 	 }

         if(current == head) {
	    newNode.next = current;
            head = newNode;	    
  	 }
         else {
	    newNode.next = current;
            previous.next = newNode;	    
  	 }
      }
   }

   public void delete(int d) {
      if(isEmpty()) 
         System.out.println("List is empty");
      else {
         Node current = head;
         Node previous = current;
         while((current.next != null) && (d > current.value)) {
            previous = current;
            current = current.next;
         }

	 //at node that is either = or > d
	 if(d == current.value) {
            //current is pointing to first value in list
            if(current == head) 
 	       head = current.next;
            else {
	       previous.next = current.next;
            }
         } 
         else 
            System.out.println("Element not in list");  
      }
   }

   //Precondition: list is not empty
   public int max() {
      Node current = head;
      while(current.next != null) {
         current = current.next;
      }

      return current.value;
   }

   //Precondition: list is not empty
   public int min() {
      return head.value;
   }

   public void print() {
      Node current = head;
      while(current != null) {
         System.out.print(current.value + " ");
         current = current.next;
      }
      System.out.println();
   }

   public boolean isEmpty() {
      if(head == null)
         return true;
      return false;
   }

}
