/*  Ryan Blair and Garrett Leone
*   rablair	   gcleone
*   Date: 11/13/15 
*   Project 4
*/

public class Student { //student class for a student object

   private long studentId; //student id
   private String name; //student last name

   public Student(long id, String lastName) { //constructor giving student an id and last name
      studentId = id;
      name = lastName;
   }
 
   public boolean equals(Object other) { //defines the compareTo method for student
      if(((Student) other).studentId - this.studentId == 0) 
         return true;
      else 
         return false;
   }
   
   public String toString() { //prints out the string for a student object
      return "{ id: " + this.studentId + ", name: " + this.name + " }";
   }

   public int hashCode() {
      Long temp = studentId;
      return temp.hashCode();
   }
   
}
