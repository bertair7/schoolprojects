/*  Ryan Blair and Garrett Leone
*   rablair	   gcleone
*   Date: 11/13/15 
*   Project 4
*/

import java.lang.*;
import java.util.*;
public class HashTable {

   private class HashEntry { //items to be entered into the hash array
      public Object item;
      public boolean isActive; 
      
      public HashEntry(Object x) {
         item = x;
         isActive = true;
      }
   }

   private HashEntry[] table;
   private int occupiedCells;

   public HashTable(int size) {
      table = new HashEntry[nextPrime(2*size)]; 
      occupiedCells = 0;
   }

   private int hash(Object x) {
      return Math.abs(x.hashCode()) % table.length;
   }
   
   private class Iter implements Iterator { 
      public int cursor;

      public Iter() {
         cursor = 0;
         boolean found = false;
         while(!found && cursor < table.length) {
            if(table[cursor] != null && table[cursor].isActive)
               found = true;
            else cursor++;
         }
      }

      public boolean hasNext() {
         return cursor < table.length;
      }

      public Object next() {
         if(!hasNext())
            throw new NoSuchElementException();    
         int tempIndex = cursor;
         cursor++;
         
         boolean found1 = false;
         while(!found1 && cursor < table.length) {
            if(table[cursor] != null && table[cursor].isActive)
               found1 = true;
            else cursor++;
         }
         return table[tempIndex].item;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }
   }

   private int findPosition(Object x) { //finds next available position
      int i = 0;
      int hashValue = hash(x);
      int index = hashValue;
      while(table[index] != null && !((table[index].item).equals(x))) { 
         i++;
         index = ((hashValue+(i*i)) % table.length);
      }      
      return index;
   }

   public void insert(Object x) { 
      int index = findPosition(x);
      if(table[index] == null) {
         HashEntry value = new HashEntry(x);
         table[index] = value;
         occupiedCells++;
         if(!(occupiedCells < table.length/2))
            rehash();
      }
      else {
         if(!table[index].isActive)
            table[index].isActive = true;
      }
   }

   private void rehash() { 
      HashEntry[] temp = table;
      table = new HashEntry[nextPrime(temp.length*2)];
      occupiedCells = 0;
      for(int i = 0; i < temp.length; i++) {
         if(temp[i] != null && temp[i].isActive) {
            int index = findPosition(temp[i].item);
            table[index] = temp[i]; 
            occupiedCells++;
         }
      }
   }

   public void delete(Object x) { //deletes object by turning it inactive
      int index = findPosition(x);
      System.out.println(index);
      if(table[index] != null && table[index].isActive)
         table[index].isActive = false;
   }

   public Object find(Object x) { //searches for object
      int index = findPosition(x);
      if(table[index] != null && table[index].isActive)
         return table[index].item;
      return null;
   }

   public int elementCount() { //counts the elements
      int count = 0;
      for(int i = 0; i < table.length; i++) {
         if(table[i] != null && table[i].isActive)
            count++;
      }
      return count;
   }

   public boolean isEmpty() { //sees if the table is empty
      for(int i = 0; i < table.length; i++) {
         if(table[i] != null && table[i].isActive)
            return false;
      }
      return true;
   }
   
   public void makeEmpty() { //makes the table empty
      table = new HashEntry[table.length];
      occupiedCells = 0;
   }  

   public void printTable() { //prints the table in specified order
      int number = 0;
      for(int i = 0; i < table.length; i++) {
         if(table[i] != null) {
            if(table[i].isActive) 
	           System.out.println("[" + i + "]: " + table[i].item.toString() + ", active");
            else
	           System.out.println("[" + i + "]: " + table[i].item.toString() + ", inactive");
         }
         else
            System.out.println("[" + i + "]: empty");
      }
   }

   public Iterator iterator() {
      return new Iter();
   }

   //Precondtion: x > 0
   private int nextPrime(int x) {
      if(x < 4)
         return x;
      if(x % 2 == 0)
         x++;
      while(!isPrime(x)) 
         x += 2;
         
       return x;
   }
   
   private boolean isPrime(int x) { //checks to see if the number is prime
      for(int i = 2; i <= Math.sqrt(x); i++) {
         if(x % i == 0)
            return false;       
      } 
      return true;
   }
}
