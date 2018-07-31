import java.lang.*;
import java.util.*;

public class HashTableSC<T> {

   private LinkedList<T> [] table;
   public HashTableSC(int val) {
      table = (LinkedList<T> []) new LinkedList[val];
      for(int i = 0; i < table.length; i++)
         table[i] = new LinkedList<T>();
   }

   public void insert(T item) { 
      int index = hash(item);
      table[index].addFirst(item);
   }

   public void delete(T item) {
      int index = hash(item);
      int location = table[index].indexOf(item);
      if(location >= 0) 
         table[index].remove(location);
   }

   public boolean find(T item) {
      int index = hash(item);
      return table[index].contains(item);      
   }

   public boolean isEmpty() {
      for(int i = 0; i < table.length; i++) {
         if(table[i].size() != 0)
            return false;
      }
      return true;
   }

   public void print() {
      for(int i = 0; i < table.length; i++) {
         System.out.print(i + ": ");
         for(int j = 0; j < table[i].size(); j++) {
	    System.out.print(table[i].get(j) + " ");
	 }
	 System.out.println();
      }
   }

   private int hash(T item) {
      return Math.abs(item.hashCode()) % table.length;
   }

}
