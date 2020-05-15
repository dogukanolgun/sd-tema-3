#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY 9999999

void dijkstra(int **graph, int *reprezentanti, int N, int X);
void printGraph(int **graph, int n, int m);

int main(int argc, char *argv[])
{
   if (argc != 2) // check input format
   {
      printf("Incorrect format.\n");
      return 0;
   }
   int N, M, X, u, v, x;
   char filename[100];
   strcpy(filename, argv[1]);
   FILE *myFile = fopen(filename, "r");
   fscanf(myFile, "%d %d %d", &N, &M, &X);
   // printf("%d %d %d\n", N, M, X);

   int **graph = (int **)malloc(N * sizeof(int *));
   for (int i = 0; i < N; i++)
      graph[i] = (int *)malloc(N * sizeof(int));
   for (int i = 0; i < N; i++) // initialize graph
      for (int j = 0; j < N; j++)
         graph[i][j] = 0;

   for (int i = 0; i < M; i++) // read graph
   {
      fscanf(myFile, "%d %d %d", &u, &v, &x);
      graph[u - 1][v - 1] = x;
      graph[v - 1][u - 1] = x;
   }
   // printGraph(graph, N, N);

   int *reprezentanti = (int *)malloc(X * sizeof(int));
   for (int i = 0; i < X; i++)
      fscanf(myFile, "%d", &reprezentanti[i]);
   // for (int i = 0; i < X; i++)
   //    printf("%d ", reprezentanti[i]);
   // printf("\n");

   dijkstra(graph, reprezentanti, N, X);

   for (int i = 0; i < N; i++)
      free(graph[i]);
   free(reprezentanti);
}

void dijkstra(int **graph, int *reprezentanti, int N, int X)
{
   int **shortestPath = (int **)malloc(X * sizeof(int *));
   for (int i = 0; i < X; i++)
      shortestPath[i] = (int *)malloc(N * sizeof(int));
   for (int i = 0; i < X; i++)
      for (int j = 0; j < N; j++)
         shortestPath[i][j] = INFINITY;
   // printGraph(shortestPath, X, N);

   for (int k = 0; k < X; k++)
   {
      int src = reprezentanti[k] - 1;
      // printf("%d\n", src);
      int **cost = (int **)malloc(N * sizeof(int *));
      for (int i = 0; i < N; i++)
         cost[i] = (int *)malloc(N * sizeof(int));
      int *distance = (int *)malloc(N * sizeof(int));
      int *pred = (int *)malloc(N * sizeof(int));
      int *visited = (int *)malloc(N * sizeof(int));

      // int cost[N][N], distance[N], pred[N];
      int /*visited[N],*/ count, mindistance, nextnode, i, j;

      //pred[] stores the predecessor of each node
      //count gives the number of nodes seen so far
      //create the cost matrix
      for (i = 0; i < N; i++)
         for (j = 0; j < N; j++)
            if (graph[i][j] == 0)
               cost[i][j] = INFINITY;
            else
               cost[i][j] = graph[i][j];

      //initialize pred[],distance[] and visited[]
      for (i = 0; i < N; i++)
      {
         distance[i] = cost[src][i];
         pred[i] = src;
         visited[i] = 0;
      }

      distance[src] = 0;
      visited[src] = 1;
      count = 1;

      while (count < N - 1)
      {
         mindistance = INFINITY;

         //nextnode gives the node at minimum distance
         for (i = 0; i < N; i++)
            if (distance[i] < mindistance && !visited[i])
            {
               mindistance = distance[i];
               nextnode = i;
            }

         //check if a better path exists through src
         visited[nextnode] = 1;
         for (i = 0; i < N; i++)
            if (!visited[i])
               if (mindistance + cost[nextnode][i] < distance[i])
               {
                  distance[i] = mindistance + cost[nextnode][i];
                  pred[i] = nextnode;
               }
         count++;
      }

      //print the path and distance of each node
      for (i = 0; i < N; i++)
         if (i != src)
         {
            // printf("Distance to %d is %d\n", i, distance[i]);
            shortestPath[k][i] = distance[i];
            // printf("Path =   %d", i);
            // j = i;
            // do
            // {
            //    j = pred[j];
            //    printf("<-%d", j);
            // } while (j != src);
            // printf("\n");
         }
         else if (i == src)
         {
            // printf("Distance to %d is %d\n", i, distance[i]);
            shortestPath[k][i] = distance[i];
         }

      for (int i = 0; i < N; i++)
         free(cost[i]);
      free(distance);
      free(pred);
      free(visited);
   }

   // printGraph(shortestPath, X, N);

   for (int j = 0; j < N; j++)
   {
      int min = INFINITY;
      int minVertex = 0;
      for (int i = 0; i < X; i++)
      {
         if (shortestPath[i][j] < min)
         {
            min = shortestPath[i][j];
            minVertex = i;
         }
      }
      if (min == INFINITY)
      {
         printf("-1\n");
      }
      else
         printf("%d %d\n", reprezentanti[minVertex], min);
   }
   for (int i = 0; i < X; i++)
      free(shortestPath[i]);
}

void printGraph(int **graph, int n, int m)
{
   for (int i = 0; i < n; i++) // printf graph
   {
      for (int j = 0; j < m; j++)
         printf("%d ", graph[i][j]);
      printf("\n");
   }
}