import java.util.Scanner;

public class StringChecker {

   public static boolean isBalanced(String thing) {
      AStack<Character> parentheses = new AStack<Character>(thing.length());
      int count = 0;
      boolean balanced = true;
 
      while(count < thing.length() && balanced) {
         switch(thing.charAt(count)) {
 	    case '(': 
	    case '{': 
            case '[': 
	       parentheses.push(thing.charAt(count));
	       count++;
               break; 
 
            case ')': 
	       if(parentheses.isEmpty())
	          balanced = false;
               else {
		  char popped = parentheses.pop();
                  if(popped.compare('(') != 0)
      		     balanced = false;
		  count++;
               }
	       break;

            case '}': 
	       if(parentheses.isEmpty())
	          balanced = false;
               else {
		  char popped = parentheses.pop();
                  if(popped.compare('{') != 0)
      		     balanced = false;
		  count++;
               }
 	       break; 
 
            case ']': 
	       if(parentheses.isEmpty())
	          balanced = false;
               else {
		  char popped = parentheses.pop();
                  if(popped.compare('[') != 0)
      		     balanced = false;
		  count++;
               }
               break;

            default:
	       count++;	                  
         }
      }
      if(!parentheses.isEmpty()) 
         balanced = false;
      return balanced;
   }

   public static void main(String[] args) {
      System.out.println("Check if you're statement is balanced");
      Scanner in = new Scanner(System.in);

      String statement = in.nextLine();
      boolean bal = isBalanced(statement);
 
      if(bal)
         System.out.println("Balanced");
      else
  	 System.out.println("Not balanced");
   }
}
