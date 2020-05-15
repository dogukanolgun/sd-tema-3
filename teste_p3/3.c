#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
   int vertex;
   struct node *next;
};
struct Graph
{
   int numVertices;
   struct node **adjLists;
};

struct node *createNode(int);
struct Graph *createGraph(int vertices);
void addEdge(struct Graph *graph, int src, int dest);
void printGraph(struct Graph *graph);
void printAllPaths(struct Graph *graph, int N, int src, int des);
void printAllPathsUtil(struct Graph *graph, int N, int src,
                       int des, int *visited, int *counter,
                       int *path, int path_index);

int main(int argc, char *argv[])
{
   if (argc != 2) // check input format
   {
      printf("Incorrect format.\n");
      return 0;
   }
   int N, M, Q, u, v, src, des;
   char filename[100];
   strcpy(filename, argv[1]);
   FILE *myFile = fopen(filename, "r");
   fscanf(myFile, "%d %d %d", &N, &M, &Q);
   // printf("%d %d %d\n", N, M, Q);

   struct Graph *graph = createGraph(N);

   for (int i = 0; i < M; i++) // read graph
   {
      fscanf(myFile, "%d %d", &u, &v);
      // printf("%d %d\n", u - 1, v - 1);
      addEdge(graph, u - 1, v - 1);
   }

   int **queries = (int **)malloc(Q * sizeof(int *));
   for (int i = 0; i < Q; i++)
      queries[i] = (int *)malloc(2 * sizeof(int));

   for (int i = 0; i < Q; i++) // read queries
   {
      fscanf(myFile, "%d %d", &src, &des);
      queries[i][0] = src - 1;
      queries[i][1] = des - 1;
   }

   // for (int i = 0; i < Q; i++)
   //    printf("%d %d\n", queries[i][0], queries[i][1]);
   // printGraph(graph);

   printAllPaths(graph, N, 0, 1);

   return 0;
}

struct node *createNode(int v)
{
   struct node *newNode = (struct node *)malloc(sizeof(struct node));
   newNode->vertex = v;
   newNode->next = NULL;
   return newNode;
}
struct Graph *createGraph(int vertices)
{
   struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
   graph->numVertices = vertices;

   graph->adjLists = (struct node **)malloc(vertices * sizeof(struct node *));

   for (int i = 0; i < vertices; i++)
      graph->adjLists[i] = NULL;

   return graph;
}
void addEdge(struct Graph *graph, int src, int dest)
{
   // Add edge from src to dest
   //    //   struct node* newNode = createNode(dest);
   //    //   newNode->next = graph->adjLists[src];
   //    //   graph->adjLists[src] = newNode;
   struct node *newNode = createNode(dest);
   struct node *temp = graph->adjLists[src];
   if (graph->adjLists[src] == NULL)
   {
      // printf("wow\n");
      graph->adjLists[src] = newNode;
   }
   else
   {
      while (temp->next)
         temp = temp->next;
      temp->next = newNode;
   }

   // Add edge from dest to src
   //     // newNode = createNode(src);
   //     // newNode->next = graph->adjLists[dest];
   //     // graph->adjLists[dest] = newNode;
   newNode = createNode(src);
   temp = graph->adjLists[dest];
   if (graph->adjLists[dest] == NULL)
   {
      // printf("wow\n");
      graph->adjLists[dest] = newNode;
   }
   else
   {
      while (temp->next)
         temp = temp->next;
      temp->next = newNode;
   }
}
void printGraph(struct Graph *graph)
{
   for (int v = 0; v < graph->numVertices; v++)
   {
      struct node *temp = graph->adjLists[v];
      printf("|| %d || ", v);
      while (temp)
      {
         printf("-> %d ", temp->vertex);
         temp = temp->next;
      }
      printf("\n");
   }
}

void printAllPaths(struct Graph *graph, int N, int src, int des)
{
   printGraph(graph);
   printf("%d %d\n", src, des);

   int *visited = (int *)malloc(N * sizeof(int));
   for (int i = 0; i < N; i++)
      visited[i] = 0;
   // printf("Visited is: ");
   // for (int i = 0; i < N; i++)
   //    printf("%d ", visited[i]);
   // printf("\n");

   int *path = (int *)malloc(N * sizeof(int));
   for (int i = 0; i < N; i++)
      path[i] = 0;
   // printf("Path is: ");
   // for (int i = 0; i < N; i++)
   //    printf("%d ", path[i]);
   printf("=============\n");

   int *counter = (int *)malloc(N * sizeof(int));
   for (int i = 0; i < N; i++)
      counter[i] = 0;

   int path_index = 0;

   printAllPathsUtil(graph, N, src, des, visited, counter, path, path_index);

   for (int i = 0; i < N; i++)
      printf("%d ", counter[i]);
   printf("\nWORKSWORKSWORKS\n");
}

void printAllPathsUtil(struct Graph *graph, int N, int src,
                       int des, int *visited, int *counter,
                       int *path, int path_index)
{
   // printf("function called -> -> -> -> continue -> -> -> ->\n");

   // Mark the current node and store it in path[]
   visited[src] = 1;
   path[path_index] = src;
   path_index++;

   // { // test purpose prints
   //    printf("index: %d. Visited is: ", path_index);
   //    for (int i = 0; i < N; i++)
   //       printf("%d ", visited[i]);
   //    // printf("\n");
   //    printf(". Path is: ");
   //    for (int i = 0; i < N; i++)
   //       printf("%d ", path[i]);
   //    printf("\n");
   // }

   // If current vertex is same as destination, then print
   // current path[]
   if (src == des)
   {
      printf("%d", path[0]);
      counter[path[0]]++;
      for (int i = 1; i < path_index; i++)
      {
         counter[path[i]]++;
         printf(" -> %d", path[i]);
      }
      printf("\n");
      // printf(" ||||||||||\n=============\n");
      // printf("=============\n");
      // printf("=============\n");
      // printf("=============\n");
      // printf("=============\n");
      if (path[1] == des)
      {
         path_index--;
         visited[src] = 0;
         path[src] = 0;
      }
   }
   else // If current vertex is not destination
   {
      // Recur for all the vertices adjacent to current vertex
      struct node *iterate = graph->adjLists[src];
      while (iterate != NULL)
      {
         int i = iterate->vertex;
         // printf("if === |%d| === hasnt been visited\n", i);
         if (!visited[i])
         {
            // printf("  ???   ??? ?  ?\n");
            printAllPathsUtil(graph, N, i, des, visited, counter, path, path_index);
         }
         // printf("|--------|\n");
         // printf("| %d ->", iterate->vertex);
         if (iterate->next == NULL)
            break;
         else
            iterate = iterate->next;

         // printf(" %d |\n|--------|\n", iterate->vertex);
      }
      // printf("================================================\n");
      // printf("================================================\n");
   }

   // Remove current vertex from path[] and mark it as unvisited
   path_index--;
   visited[src] = 0;
   path[path_index] = 0;
   // printf("| END | index: %d. src: %d. Visited: ", path_index, src);
   // for (int i = 0; i < N; i++)
   //    printf("%d ", visited[i]);
   // printf(".Path: ");
   // for (int i = 0; i < N; i++)
   //    printf("%d ", path[i]);
   // printf("\n");
} /*

|| 0 || -> 4 -> 3 -> 2
|| 1 || -> 3
|| 2 || -> 4 -> 3 -> 0
|| 3 || -> 2 -> 1 -> 0
|| 4 || -> 2 -> 0

*/