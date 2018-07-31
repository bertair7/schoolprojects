// Ryan Blair rablair
// Ruslan Adamovics radamovi
// Project 2
// (Data Fininshed)

import java.util.*;
import java.io.*;

public class MatrixWork {

   public static int[][] matrixProduct(int[][] A, int[][] B) {
      int[][] C = new int[A.length][B[0].length];
      
      if (A[0].length != B.length) {
         throw new IllegalArgumentException();
      }

      for (int x = 0; x < A.length; x++) {
         for (int y = 0; y < B[0].length; y++) {
            int total = 0;
            for (int i = 0; i < A[0].length; i++) {
               total += A[x][i] * B[i][y];
            }
            C[x][y] = total;
         }
      }
      return C;
   }

   public static void main(String[] args) throws IOException {
      System.out.format("Enter a file name: ");
      Scanner s = new Scanner(System.in);
      File input = new File(s.nextLine());
      Scanner in = new Scanner(input);

      int lenA = in.nextInt();
      int colA = in.nextInt();
      int[][] A = new int[lenA][colA];

      for (int x = 0; x < lenA; x++) {
         for (int y = 0; y < colA; y++) {
            A[x][y] = in.nextInt();
         }
      }

      int lenB = in.nextInt();
      int colB = in.nextInt();
      int[][] B = new int[lenB][colB];

      for (int x = 0; x < lenB; x++) {
         for (int y = 0; y < colB; y++) {
            B[x][y] = in.nextInt();
         }
      }
 
      try {
         int[][] C = MatrixProduct.matrixProduct_DAC(A, B);
         System.out.format("DAC Product matrix: \n");
         for (int x = 0; x < lenA; x++) {
            for (int y = 0; y < colB; y++) {
               System.out.format("%d ", C[x][y]);
            }
            System.out.format("\n");
         }
         int[][] D = MatrixProduct.matrixProduct_Strassen(A, B);
         System.out.format("Strassen Product matrix: \n");
         for (int x = 0; x < lenA; x++) {
            for (int y = 0; y < colB; y++) {
               System.out.format("%d ", D[x][y]);
            }
            System.out.format("\n");
         }
      }
      catch (IllegalArgumentException e) {
         System.out.format("Incompatible matrices\n");
      } 
   }     
}
