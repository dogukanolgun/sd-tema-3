#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) // check input format
    {
        printf("Incorrect format.\n");
        return 0;
    }
    int N, M, u, v, x, prev_u = 0, prev_v = 0, prev_x = 0;
    char filename[100];
    strcpy(filename, argv[1]);
    FILE *myFile = fopen(filename, "r"); // read file
    fscanf(myFile, "%d %d", &N, &M);
    printf("%d %d\n", N, M);

    int **graph = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        graph[i] = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            graph[i][j] = 0;

    fscanf(myFile, "%d %d %d", &u, &v, &x);
    // printf("%d %d %d\n", u, v, x);
    // read data from input file and create adjacency matrix
    while (u != prev_u || v != prev_v || x != prev_x) // create graph
    {
        prev_u = u;
        prev_v = v;
        prev_x = x;
        graph[u - 1][v - 1] = x;
        graph[v - 1][u - 1] = x;
        printf("%d %d %d\n", u, v, x);
        fscanf(myFile, "%d %d %d", &u, &v, &x);
    }

    for (int i = 0; i < N; i++) // printf graph
    {
        for (int j = 0; j < N; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }

    wow
}