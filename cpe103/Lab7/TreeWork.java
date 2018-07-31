import java.lang.Math;
public class TreeWork <T> {

   public static <T extends Comparable<? super T>> boolean isHeap(T[] arr, int N) {
      int pIndex = 0;
      boolean heap = true;
 
      while(pIndex < N/2) {
      
         if(arr[pIndex].compareTo(arr[pIndex*2 + 1]) <= 0)  {
            if((pIndex*2 + 2) < N) {
               if(arr[pIndex].compareTo(arr[pIndex*2 + 2]) <= 0)
                  heap = true;
               else {
                  heap = false;
                  break;
               }
            }
         }
         else {
            heap = false;
            break;
         }
      }
      return heap;
   }

   public static <T> void printTree(T[] arr, int N) {

      int height = (int)(Math.log(N) / Math.log(2)); 
      int k = 0;

      for(int i = 0; i < height; i++) {
         for(int j = 0; j < Math.pow(i, 2); j++) {
            System.out.print(arr[k] + " ");
            k++;
         } 
         System.out.println();
      }
      for(; k < N; k++) {
         System.out.print(arr[k] + " ");
      }
      System.out.println();
   }
}