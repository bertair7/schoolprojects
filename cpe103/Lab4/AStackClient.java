import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.File;
import java.io.IOException;

public class AStackClient {

   public static void main(String[] args) throws IOException{
      Scanner in = new Scanner(System.in);
      Scanner fileScan;
      AStack<Integer> integers = new AStack<Integer>(5);
      AStack<Float> floats = new AStack<Float>(5);
      AStack<String> strings = new AStack<String>(5);

      System.out.print("Input file name: ");
      try {
         fileScan = new Scanner(new File(in.next()));
         while(fileScan.hasNext()) {
            if(fileScan.hasNextInt()) 
               integers.push(fileScan.nextInt());
            else if(fileScan.hasNextFloat()) 
               floats.push(fileScan.nextFloat());
            else
               strings.push(fileScan.next());
         }
         fileScan.close();

         System.out.print("Strings: ");
         while(!strings.isEmpty()) {
            System.out.print(strings.pop() + " ");
         }
         System.out.println();

         System.out.print("Floats: ");
         while(!floats.isEmpty()) {
            System.out.print(floats.pop() + " ");
         }
         System.out.println();

         System.out.print("Integers: ");
         while(!integers.isEmpty()) {
            System.out.print(integers.pop() + " ");
         }
         System.out.println();
      }
      catch(FileNotFoundException e) {
         System.out.println("Invalid file");
      }  
      in.close();
   }
}