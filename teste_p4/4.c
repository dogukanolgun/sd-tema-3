#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printGraph(int **graph, int n, int m);
void set_solve(int **graph, int *directii, int N, int M, int K);
void solve(int **graph, int **visited, int *directii,
           int index, int *count, int N, int M, int K, int r, int c);

int main(int argc, char *argv[])
{
    if (argc != 2) // check input format
    {
        printf("Incorrect format.\n");
        return 0;
    }
    int N, M, K, x;
    char filename[100];
    strcpy(filename, argv[1]);
    FILE *myFile = fopen(filename, "r");
    fscanf(myFile, "%d %d %d", &N, &M, &K);
    printf("%d %d %d\n", N, M, K);

    int **graph = (int **)calloc(N, sizeof(int *));
    for (int i = 0; i < N; i++)
        graph[i] = (int *)calloc(M, sizeof(int));
    for (int i = 0; i < N; i++) // initialize graph
        for (int j = 0; j < N; j++)
            graph[i][j] = 0;

    for (int i = 0; i < N; i++) // read graph
    {
        for (int j = 0; j < M; j++)
        {
            fscanf(myFile, "%d", &x);
            graph[i][j] = x;
        }
    }

    printGraph(graph, N, M);

    int *directii = (int *)calloc((K + 1), sizeof(int));
    for (int i = 0; i < K; i++)
        fscanf(myFile, "%d", &directii[i]);
    directii[K] = 9;
    for (int i = 0; i < K; i++)
        printf("%d ", directii[i]);
    printf("\n\n");

    set_solve(graph, directii, N, M, K);

    // FREE WORLD
    free(myFile);
    for (int i = 0; i < N; i++)
        free(graph[i]);
    free(graph);
    free(directii);
}

void printGraph(int **graph, int n, int m)
{
    for (int i = 0; i < n; i++) // printf graph
    {
        for (int j = 0; j < m; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
    printf("\n");
}

void set_solve(int **graph, int *directii, int N, int M, int K)
{
    int r, c;
    int *count = (int *)calloc(1, sizeof(int));
    printf("%d %d %d\n", N, M, K);

    int **visited = (int **)calloc(N, sizeof(int *));
    printf("TEST!\n");
    for (int i = 0; i < N; i++)
        visited[i] = (int *)calloc(M, sizeof(int));
    for (int i = 0; i < N; i++) // initialize graph
        for (int j = 0; j < M; j++)
        {
            visited[i][j] = graph[i][j];
            if (graph[i][j] == 2)
            {
                r = i;
                c = j;
            }
        }
    int index = 0;

    printf("Starting Point is: [%d %d]\n", r, c);
    solve(graph, visited, directii, index, count, N, M, K, r, c);

    printf("RESULT: %d\n", count[0]);

    // FREE WORLD
    for (int i = 0; i < N; i++)
        free(visited[i]);
    free(visited);
    free(count);
}

void solve(int **graph, int **visited, int *directii,
           int index, int *count, int N, int M, int K, int r, int c)
{
    int r_vec, c_vec;

    int d_row[4] = {-1, 1, 0, 0};
    int d_col[4] = {0, 0, -1, 1};

    r_vec = r + d_row[directii[index]];
    c_vec = c + d_col[directii[index]];

    if (directii[index] == 9)
        return;

    // dont let it overflow
    if (r_vec < 0 || r_vec > N - 1 || visited[r_vec][c_vec] == 1 ||
        c_vec < 0 || c_vec > M - 1 || /* visited[r_vec][c_vec] == 8 ||*/
        visited[r_vec][c_vec] == 2)
        return;

    // { // test print before every new graph
    //     printf("| %d | Path: -> [%d %d], and directii: ", index, r_vec, c_vec);
    //     int all = index;
    //     do
    //     {
    //         int switch_var = directii[all];
    //         switch (switch_var)
    //         {
    //         case 0:
    //             printf("U ");
    //             break;
    //         case 1:
    //             printf("D ");
    //             break;
    //         case 2:
    //             printf("L ");
    //             break;
    //         case 3:
    //             printf("R ");
    //             break;
    //         }
    //         // printf("%d ", directii[all]);
    //         all++;
    //     } while (all < K);
    //     printf("\n");
    // }
    visited[r_vec][c_vec] = 8;
    // printGraph(visited, N, M);

    // continue going straight
    solve(graph, visited, directii, index, count, N, M, K, r_vec, c_vec);

    // change your direction
    // printf("new direction now: %d:\n", directii[index + 1]);
    if (directii[index + 1] == 9)
        count[0]++;
    index++;
    solve(graph, visited, directii, index, count, N, M, K, r_vec, c_vec);

    ///////////
    visited[r_vec][c_vec] = 0;
    index--;
    // printf("---------------\n");
    // printGraph(visited, N, M);

    // printf("|||||||||||||||||||||||||||||||||||\n");
}
