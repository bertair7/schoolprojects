import java.util.*;
public class SeparateAndMerge {

   public static void main(String[] args) {
      LList<Float> listFloat = new LList<Float>();
      LList<Integer> listInt = new LList<Integer>();

      Scanner in = new Scanner(System.in);
      System.out.println("Please input numbers");
      while(in.hasNext()) {
         if(in.hasNextInt()) {
            int hold = in.nextInt();
            listInt.add(hold);
         }
         else if(in.hasNextFloat()) {
            float hold1 = in.nextFloat();
            listFloat.add(hold1);
         }
         else 
            in.next();
         
      }
      in.close();
      Iterator<Integer> itr = listInt.iterator();
      Iterator<Float> itr2 = listFloat.iterator();

      System.out.print("Inputted values: ");
      while(itr2.hasNext() || itr.hasNext()) {
         if(itr.hasNext())        
            System.out.print(itr.next() + " ");
         if(itr2.hasNext())        
            System.out.print(itr2.next() + " ");
      }
      System.out.println();
   }

}
