/* Ryan Blair (rablair) and Garrett Leone (geleone)
 * Project 4
 * Date: 11/13/15
 */
 
import java.util.*;
import java.io.*;
public class HTDriver {

   public static void main(String args[]) throws IOException { //tests out the hash table and student classes
      Scanner in = new Scanner(System.in);
      Scanner fileScan;
      
      boolean isDone = false;

      //prompt for file of students
      System.out.print("File name for student data: ");
      fileScan = new Scanner(new File(in.nextLine()));
      int total = fileScan.nextInt();
      HashTable test = new HashTable(total); 
      fileScan.nextLine();
      for(int i = 0; i < total; i++) {
         Scanner lineScan = new Scanner(fileScan.nextLine());
            if(lineScan.hasNextLong()) {			//check for id
               long studentID = lineScan.nextLong();
	           if(studentID > 0) {				//check if positive
		           if(lineScan.hasNext()) {			//check for name
		              String studentName = lineScan.next();
		              if(!lineScan.hasNext()) {			//check for additional values
			             Student temp = new Student(studentID, studentName);
			             test.insert(temp);
 		              }
		           }
	            }
	         }
              
         }

      //menu
      System.out.println("Choose one of the following operations by entering the provided letter:");
      System.out.println("\ta - add the element");
      System.out.println("\td - delete the element");
      System.out.println("\tf - find and retrieve the element");
      System.out.println("\tn - get the number of elements in the collection");
      System.out.println("\te - check if the collection is empty");
      System.out.println("\tk - make the hash table empty");
      System.out.println("\tp - print the content of the hash table");
      System.out.println("\to - output the elements of the collection");
      System.out.println("\tq - Quit the program");


      while(!isDone) { //checking to see when done
         String str = in.nextLine();
         switch(str) {
            case "a": //insert
               System.out.print("Student record: ");
               Scanner lineScan1 = new Scanner(in.nextLine());
               if(lineScan1.hasNextLong()) {			//check for id
                  long studentIDa = lineScan1.nextLong();
	              if(studentIDa > 0) {				//check if positive
		             if(lineScan1.hasNext()) {			//check for name
		                String studentNameA = lineScan1.next();
		                if(!lineScan1.hasNext()) {			//check for additional values
			               Student tempA = new Student(studentIDa, studentNameA);
			               test.insert(tempA);
			               System.out.println("New student inserted");
			            }
			            else 
			               System.out.println("Invalid input");
			         }
			         else 
			            System.out.println("Invalid input");
			      }
			      else 
			         System.out.println("Invalid input");
			   }
			   else 
			         System.out.println("Invalid input");
               break;

            case "d": //delete
               System.out.print("Student id: ");
               Scanner lineScan2 = new Scanner(in.nextLine());
               if(lineScan2.hasNextLong()) {			//check for id
                  long studentIDd = lineScan2.nextLong();
			      Student tempD = new Student(studentIDd, "");
			      if(test.find(tempD) != null) {
                     System.out.println(test.find(tempD).toString() + " deleted");
                     test.delete(tempD);
	              }  
	              else 
		             System.out.println("not in the hash table");   
		        }    
	           break;            

            case "f": //find and retrieve
	           System.out.print("Student id: ");
               Scanner lineScan3 = new Scanner(in.nextLine());
               if(lineScan3.hasNextLong()) {			//check for id
                  long studentIDf = lineScan3.nextLong();
			      Student tempF = new Student(studentIDf, "");
			      if(test.find(tempF) != null) 
		             System.out.println(test.find(tempF) + " is in the hash table");
	              else
		             System.out.println("This student is not in the hash table");
			   } 	            
	           break;
          
            case "n": //get number 
	           int size = test.elementCount();
	           System.out.println("The size of the hash table is: " + size);
	           break;
	             
            case "e": //check if empty
	           if(test.isEmpty())
		          System.out.println("The hash table is empty");
	           else
		          System.out.println("The hash table is not empty");
	           break;   
	           
            case "k": //make hash table empty
	           test.makeEmpty();
	           System.out.println("The hash table is now empty");
	           break;       

            case "p": //print whole collection
	           test.printTable();
	           break;

            case "o": //print using Student toString
	           Iterator iter = test.iterator();
	           while(iter.hasNext()) {
		          Object temp = iter.next();
		          System.out.println(temp.toString());
	           }
	           break; 

            case "q": //quit method
               System.out.println("Goodbye");
               in.close();
	           isDone = true;
               break;
            
            default:
               System.out.println("Invalid choice");
               break;
         }
      }   
   }
}
