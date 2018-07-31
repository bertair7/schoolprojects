/* Ryan Blair (rablair) and Garrett Leone (geleone)
 * Project 4
 * Date: 11/14/15
 */
import java.util.Scanner;
public class HTDriver {

   public static void main(String args[]) { //tests out the hash table and student classes
   
      Scanner in = new Scanner(System.in);
      Scanner fileScan;
      HashTable<Student> test = new HashTable<Student>(); 
      boolean isDone = false;

      //prompt for file of students
      System.out.print("File name for student data: ");
      try {
         fileScan = new Scanner(new File(in.next()));
         int total = fileScan.nextInt();
         for(int i = 0; i < total; i++) {
            if(fileScan.hasNextLong()) {			//check for id
               long studentID = fileScan.nextLong();
	       if(id > 0) {					//check if positive
		  if(fileScan.hasNext()) {			//check for name
		     String studentName = fileScan.next();
		     if(!fileScan.hasNext()) {			//check for additional values
			Student temp = new Student(studentID, studentName);
			test.insert(temp);
 		     }
		  }
	       }
	    }
         }
      }
      catch(FileNotFoundException e) {
         System.out.println("Invalid file");
      } 
      fileScan.close(); 

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
               System.out.print("Student ID: ");
               long valID = in.nextInt();
               System.out.print("\nStudent Last Name: ");
               String valName = in.next();
	       Student tempA = new Student(valID, valName);
	       test.insert(tempA);
               System.out.println("\nNew student inserted");
               in.nextLine();
               break;

            case "d": //delete
               System.out.print("Student ID: ");
               long valID = in.nextInt();
               System.out.print("\nStudent Last Name: ");
               String valName = in.next();
	       Student tempD = new Student(valID, valName);
               if(test.find(tempD) != null) {
                  test.delete(tempD);
                  System.out.println("\n" + valName + " deleted");
	       }
	       else 
		  System.out.println("\n" + valName + " is not in the hash table");
               in.nextLine();	       
	       break;            

            case "f": //find and retrieve
	       System.out.print("Student ID: ");
               long valID = in.nextInt();
               System.out.print("\nStudent Last Name: ");
               String valName = in.next();
               Student tempF = new Student(valID, valName);
	       if(test.find(tempF) != null) 
		  System.out.println("This student is in the hash table");
	       else
		  System.out.println("This student is not in the hash table");
	       in.nextLine();	       
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
	       Iterator<Student> iter = test.iterator();
	       
	       break;

            case "o": //print using Student toString
	       Iterator<Student> iter = test.iterator();
	       while(iter.hasNext()) {
		  Student temp = iter.next();
		  System.out.println(temp.toString());
	       }
	       break; 

            case "q": //quit method
               System.out.println("Quitting");
               in.close();
	       isDone = true;
               System.out.println();
               break;
            
            default:
               System.out.println("Invalid choice");
               break;
         }
      }   
   }
}
