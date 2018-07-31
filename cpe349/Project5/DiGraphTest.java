// Ryan Blair rablair
// Ruslan Adamovics radamovi
// Project 5
// (Data Fininshed)

import java.util.*;
import java.io.*;
import java.lang.Exception;

public class DiGraphTest {

   public static void main(String[] args) throws IOException {
      Scanner s = new Scanner(System.in);
      System.out.format("Enter the number of vertices in the graph: ");
      int v = s.nextInt();
      DiGraph graph = new DiGraph(v);
      s.nextLine();

      System.out.format("Choose one of the following operations:\n");
      System.out.format("- add edge (enter a)\n");
      System.out.format("- delete edge (enter d)\n");
      System.out.format("- edge count (enter e)\n");
      System.out.format("- vertex count (enter v)\n");
      System.out.format("- print graph (enter p)\n");
      System.out.format("- topological sort (enter t)\n");
      System.out.format("- is there a path (enter i)\n");
      System.out.format("- length of path (enter l)\n");
      System.out.format("- shortest path (enter s)\n");
      System.out.format("- print breadth-first tree (enter b)\n");
      System.out.format("- Quit (enter q)\n");

      boolean continueLoop = true;

      while (continueLoop) {
         System.out.format("\nEnter a command: ");
         String next = s.nextLine();

         switch (next) {
            case "a":
               System.out.format("Enter from and to edges: ");
               int addfrom = s.nextInt();
               int addto = s.nextInt();
               s.nextLine();
               graph.addEdge(addfrom, addto);
               System.out.format("(%d,%d) edge added\n", addfrom, addto);
               break;
            case "d":
               System.out.format("Enter from and to edges: ");
               int delfrom = s.nextInt();
               int delto = s.nextInt();
               s.nextLine();
               graph.deleteEdge(delfrom, delto);
               System.out.format("(%d,%d) edge removed\n", delfrom, delto);
               break;
            case "e":
               int edges = graph.edgeCount();
               System.out.format("Number of edges is %d\n", edges);
               break;
            case "v":
               int vertices = graph.vertexCount();
               System.out.format("Number of vertices is %d\n", vertices);
               break;
            case "p":
               System.out.format("The graph is the following:");
               graph.print();
               break;
            case "t":
               try {
                  int[] result = graph.topSort();
                  
                  for (int i = 0; i < result.length; i++) {
                     if (i == 0)
                        System.out.format("%d", result[i]+1);
                     else
                        System.out.format(", %d", result[i]+1);
                  }
                  System.out.format("\n");
               }
               catch (IllegalArgumentException e) {
                  System.out.format("The graph is cyclic\n"); 
               }
               break;
            case "i":
               System.out.format("Enter from and to edges: ");
               int isfrom = s.nextInt();
               int isto = s.nextInt();
               s.nextLine();
               boolean path = graph.isTherePath(isfrom, isto);
               if (path)
                  System.out.format("A path exists from %d to %d\n", isfrom, isto);
               else
                  System.out.format("A path does not exist from %d to %d\n", isfrom, isto);
               break;
            case "l":
               System.out.format("Enter from and to edges: ");
               int lenfrom = s.nextInt();
               int lento = s.nextInt();
               s.nextLine();
               int len = graph.lengthOfPath(lenfrom, lento);
               if (len > 0)
                  System.out.format("Length from %d to %d is %d\n", lenfrom, lento, len);
               else
                  System.out.format("Length from %d to %d is non-existant\n", lenfrom, lento);
               break;
            case "s":
               System.out.format("Enter from and to edges: ");
               int shortfrom = s.nextInt();
               int shortto = s.nextInt();
               s.nextLine();
               graph.printPath(shortfrom, shortto);
               break;
            case "b":
	       System.out.format("Enter source vertex: ");
               int source = s.nextInt();
               s.nextLine();
               graph.printTree(source);
               break;
            case "q":
               System.out.format("Goodbye\n");
               continueLoop = false;
               break;
            default:
               System.out.format("Illegal Operation\n");
               break;
         }
      }
      s.close();
   }     
}
