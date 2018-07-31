
import java.util.*;
import java.lang.Exception;

public class DiGraph {

   private LinkedList<Integer>[] graph;

   private class VertexInfo {
      int length;
      int predecessor;
   }

   private class TreeNode {
      int vertex;
      LinkedList<TreeNode> children;
   }

   public DiGraph(int N) {
      graph = new LinkedList[N];

      for (int i = 0; i < N; i++) {
         graph[i] = new LinkedList<Integer>();
      }
   }

   public void addEdge(int from, int to) {
      if (from > graph.length || to > graph.length)
         System.out.format("Illegal Edge\n");
      else if (!graph[from-1].contains(to-1)) 
         graph[from-1].add(to-1);
      else
         System.out.format("Edge already exists\n");
   }

   public void deleteEdge(int from, int to) {
      if (from > graph.length || to > graph.length)
         System.out.format("Illegal Edge\n");
      else if (graph[from-1].contains(to-1)) {
         int ind = graph[from-1].indexOf(to-1);
         graph[from-1].remove(ind);
      }
      else
         System.out.format("Edge does not exist\n");
   }

   public int edgeCount() {
      int total = 0;

      for (int i = 0; i < graph.length; i++) {
         total += graph[i].size();
      }
      return total;
   }

   public int vertexCount() {
      return graph.length;
   }

   public void print() {
      boolean first = true;

      for (int i = 0; i < graph.length; i++) {
         first = true;
         System.out.format("\n%d is connected to: ", i+1);
         for (int j = 0; j < graph[i].size(); j++) {
            if(first) {
               System.out.format("%d", graph[i].get(j)+1);
               first = false;
            }
            else {
               System.out.format(", %d", graph[i].get(j)+1);
            }
         }
      }
      System.out.format("\n");
   }

   // part 2
   private int[] indegrees() {
      int[] in = new int[graph.length];
      for (int ind = 0; ind < graph.length; ind++) {
         in[ind] = 0;
      }

      for (int i = 0; i < graph.length; i++) {
         for (int j = 0; j < graph[i].size(); j++) {
            int x = graph[i].get(j);
            in[x]++;
         }
      }
      return in;
   }

   public int[] topSort() {
      int[] indegrees = indegrees();
      int[] result = new int[graph.length];
      int resIndex = 0;

      Queue<Integer> q = new LinkedList<Integer>();
      for (int i = 0; i < graph.length; i++) {
         if (indegrees[i] == 0) 
            q.add(i);
      }

      while (!q.isEmpty()) {
         int x = q.remove();
         result[resIndex] = x;
         resIndex++;

         for (int j = 0; j < graph[x].size(); j++) {
            int y = graph[x].get(j);
            indegrees[y]--;

            if (indegrees[y] == 0)
               q.add(y);
         }         
      }
      
      if (resIndex != graph.length)
         throw new IllegalArgumentException();
  
      return result;
   }

   // part 3
   private VertexInfo[] BFS(int s) {
      int N = graph.length;
      VertexInfo[] VA = new VertexInfo[N];

      for (int i = 0; i < N; i++) {
         VA[i] = new VertexInfo();
         VA[i].length = -1;
         VA[i].predecessor = -1;
      }

      VA[s].length = 0;
      Queue<Integer> q = new LinkedList<Integer>();
      q.add(s);

      while (!q.isEmpty()) {
         int x = q.remove();
         for (int j = 0; j < graph[x].size(); j++) {
            int u = graph[x].get(j);
            if (VA[u].length == -1) {
               VA[u].length = VA[x].length + 1;
               VA[u].predecessor = x;
               q.add(u);
            }
         }
      }

      return VA;
   }

   public boolean isTherePath(int from, int to) {
      VertexInfo[] VA = BFS(from-1);

      if (VA[to-1].length == -1)
         return false;
      return true;
   }
 
   public int lengthOfPath(int from, int to) {
      VertexInfo[] VA = BFS(from-1);
    
      if (VA[to-1].length == -1)
         return 0;
      return VA[to-1].length;
   }

   public void printPath(int from, int to) {
      VertexInfo[] VA = BFS(from-1);
      int x = to-1;

      if (VA[x].length == -1) 
         System.out.format("There is no path from %d to %d\n", from, to);
      else {
         String output = "";
         while (from != x+1) {
            output = "->" + (x+1) + output;
            x = VA[x].predecessor;
         }
         output = from + output;
         System.out.format("%s\n", output);
      }
   }

   // part 4
   private TreeNode buildTree(int s) {
      VertexInfo[] VA = BFS(s-1);
      TreeNode[] tree = new TreeNode[VA.length];

      for (int i = 0; i < tree.length; i++) {
         tree[i] = new TreeNode();
         tree[i].vertex = i;
         tree[i].children = new LinkedList<TreeNode>();
      }

      for (int i = 0; i < VA.length; i++) {
         int pred = VA[i].predecessor;
         if (pred != -1)
            tree[pred].children.add(tree[i]);
      }
 
      return tree[s-1];
   }

   public void printTree(int s) {
      TreeNode tree = buildTree(s);
      printTree(tree, "");
   }

   private void printTree(TreeNode tree, String indent) {
      if (tree != null) {
         System.out.println(indent + (tree.vertex+1));
         indent += "    ";
         for (int i = 0; i < tree.children.size(); i++) {
            printTree(tree.children.get(i), indent);
         }
      }
   }//
}
