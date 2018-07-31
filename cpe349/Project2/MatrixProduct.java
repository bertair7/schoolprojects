// Ryan Blair rablair
// Ruslan Adamovics radamovi
// Project 2 Pt 2
// 2/2/17

import java.util.*;

public class MatrixProduct {

   private static void checkMatrices(int[][] A, int[][] B) {
      if ((A.length != A[0].length) || (B.length != B[0].length)) {
         throw new IllegalArgumentException();
      }
      if (A[0].length != B.length) {
         throw new IllegalArgumentException();
      }
      if ((A.length & (A.length - 1)) != 0)
         throw new IllegalArgumentException();
   }

   public static int[][] matrixProduct_DAC(int[][] A, int[][] B) {
      checkMatrices(A, B);
      int[][] C = MatrixDAC(A, 0, 0, B, 0, 0, A.length);
      return C;
   }

   private static int[][] MatrixDAC(int[][] A, int srowA, int scolA, 
      int[][] B, int srowB, int scolB, int n) {
      int[][] C = new int[n][n];
      if (n == 1)
         C[0][0] = A[srowA][scolA] * B[srowB][scolB];
      else {
         int[][] A11 = splitMatrix(A, n/2, 0, 0);
         int[][] A12 = splitMatrix(A, n/2, 0, n/2);
         int[][] A21 = splitMatrix(A, n/2, n/2, 0);
         int[][] A22 = splitMatrix(A, n/2, n/2, n/2);

         int[][] B11 = splitMatrix(B, n/2, 0, 0);
         int[][] B12 = splitMatrix(B, n/2, 0, n/2);
         int[][] B21 = splitMatrix(B, n/2, n/2, 0);
         int[][] B22 = splitMatrix(B, n/2, n/2, n/2);

         int[][] C11 = addMatrices(matrixProduct_DAC(A11, B11), 
            matrixProduct_DAC(A12, B21));
         int[][] C12 = addMatrices(matrixProduct_DAC(A11, B12), 
            matrixProduct_DAC(A12, B22));
         int[][] C21 = addMatrices(matrixProduct_DAC(A21, B11), 
            matrixProduct_DAC(A22, B21));
         int[][] C22 = addMatrices(matrixProduct_DAC(A21, B12), 
            matrixProduct_DAC(A22, B22));

         joinMatrix(C11, C, 0, 0);
         joinMatrix(C12, C, 0, n/2);
         joinMatrix(C21, C, n/2, 0);
         joinMatrix(C22, C, n/2, n/2);
      }
      return C;
   }

   private static int[][] addMatrices(int[][] X, int[][] Y) {
      int[][] Z = new int[X.length][X[0].length];
      for (int i = 0; i < X.length; i++) {
         for (int j = 0; j < X.length; j++) {
            Z[i][j] = X[i][j] + Y[i][j];
         }
      }
      return Z;
   } 

   private static int[][] subMatrices(int[][] X, int[][] Y) {
      int[][] Z = new int[X.length][X.length];
      for (int i = 0; i < X.length; i++) {
         for (int j = 0; j < X.length; j++) {
            Z[i][j] = X[i][j] - Y[i][j];
         }
      }
      return Z;
   } 

   private static void joinMatrix(int[][] C, int[][] P, int i, int j) {
      for (int x = 0, x2 = i; x < C.length; x++, x2++) {
         for (int y = 0, y2 = j; y < C.length; y++, y2++) {
            P[x2][y2] = C[x][y];
         }
      }
   }

   public static int[][] matrixProduct_Strassen(int[][] A, int[][] B) throws 
      IllegalArgumentException {
      checkMatrices(A, B);
      int[][] C = MatrixStrassen(A, 0, 0, B, 0, 0, A.length);
      return C;
   }

   private static int[][] MatrixStrassen(int[][] A, int srowA, int scolA, 
      int[][] B, int srowB, int scolB, int n) {
      int[][] C = new int[n][n];
      if (n == 1)
         C[0][0] = A[srowA][scolA] * B[srowB][scolB];
      else {
         int[][] A11 = splitMatrix(A, n/2, 0, 0);
         int[][] A12 = splitMatrix(A, n/2, 0, n/2);
         int[][] A21 = splitMatrix(A, n/2, n/2, 0);
         int[][] A22 = splitMatrix(A, n/2, n/2, n/2);

         int[][] B11 = splitMatrix(B, n/2, 0, 0);
         int[][] B12 = splitMatrix(B, n/2, 0, n/2);
         int[][] B21 = splitMatrix(B, n/2, n/2, 0);
         int[][] B22 = splitMatrix(B, n/2, n/2, n/2);

         int[][] s1 = subMatrices(B12, B22);
         int[][] s2 = addMatrices(A11, A12);
         int[][] s3 = addMatrices(A21, A22);
         int[][] s4 = subMatrices(B21, B11);
         int[][] s5 = addMatrices(A11, A22);
         int[][] s6 = addMatrices(B11, B22);
         int[][] s7 = subMatrices(A12, A22);
         int[][] s8 = addMatrices(B21, B22);
         int[][] s9 = subMatrices(A11, A21);
         int[][] s10 = addMatrices(B11, B12);

         int[][] p1 = matrixProduct_Strassen(A11, s1);
         int[][] p2 = matrixProduct_Strassen(s2, B22);
         int[][] p3 = matrixProduct_Strassen(s3, B11);
         int[][] p4 = matrixProduct_Strassen(A22, s4);
         int[][] p5 = matrixProduct_Strassen(s5, s6);
         int[][] p6 = matrixProduct_Strassen(s7, s8);
         int[][] p7 = matrixProduct_Strassen(s9, s10);
         
         int[][] C11 = addMatrices(subMatrices(addMatrices(p5, p4), p2), p6);
         int[][] C12 = addMatrices(p1, p2);
         int[][] C21 = addMatrices(p3, p4);
         int[][] C22 = subMatrices(subMatrices(addMatrices(p5, p1), p3), p7);

         joinMatrix(C11, C, 0, 0);
         joinMatrix(C12, C, 0, n/2);
         joinMatrix(C21, C, n/2, 0);
         joinMatrix(C22, C, n/2, n/2);
         
      }
      return C;
   }

   private static int[][] splitMatrix(int[][] Bigger, int size, int i, int j) {
      int[][] Smaller = new int[size][size];
      for (int x = 0, x2 = i; x < size; x++, x2++) {
         for (int y = 0, y2 = j; y < size; y++, y2++) {
            Smaller[x][y] = Bigger[x2][y2];
         }
      }
      return Smaller;
   }
}
