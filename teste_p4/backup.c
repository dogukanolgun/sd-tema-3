#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printGraph(int **graph, int n, int m);
void set_solve(int **graph, int *directii, int N, int M, int K);
void solve(int **graph, int **visited, int *directii,
           int index, int N, int M, int K, int r, int c);

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

    int **graph = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        graph[i] = (int *)malloc(M * sizeof(int));
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

    int *directii = (int *)malloc(K * sizeof(int));
    for (int i = 0; i < K; i++)
        fscanf(myFile, "%d", &directii[i]);
    directii[K] = 9;
    for (int i = 0; i < K; i++)
        printf("%d ", directii[i]);
    printf("\n\n");

    set_solve(graph, directii, N, M, K);

    for (int i = 0; i < N; i++)
        free(graph[i]);
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
    int **visited = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        visited[i] = (int *)malloc(M * sizeof(int));
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
    solve(graph, visited, directii, index, N, M, K, r, c);

    printf("==========================================\n");
    printf("==========================================\n");
    printf("==========================================\n");
    printf("==========================================\n");
}

void solve(int **graph, int **visited, int *directii,
           int index, int N, int M, int K, int r, int c)
{
    int r_cont, c_cont, r_next, c_next;

    int d_row[4] = {-1, 1, 0, 0};
    int d_col[4] = {0, 0, -1, 1};

    r_cont = r + d_row[directii[index]];
    c_cont = c + d_col[directii[index]];

    r_next = r + d_row[directii[index + 1]];
    c_next = c + d_col[directii[index + 1]];

    { // test print before every new graph
        printf("| %d | Path: -> [%d %d], Path next: -> [%d %d] and directii: ",
               index, r_cont, c_cont, r_next, c_next);
        int all = index;
        do
        {
            printf("%d ", directii[all]);
            all++;
        } while (all < K);
        printf("\n");
    }

    visited[r_vec][c_vec] = 8;
    printGraph(visited, N, M);

    solve(graph, visited, directii, index, N, M, K, r_cont, c_cont);

    solve(graph, visited, directii, index, N, M, K, r_next, c_next);

    /////////////////////////////////
    // int r_vec, c_vec;

    // int d_row[4] = {-1, 1, 0, 0};
    // int d_col[4] = {0, 0, -1, 1};

    // for (int i = 0; i < 4; i++)
    // {
    //     r_vec = r + d_row[i];
    //     c_vec = c + d_col[i];

    //     // dont let it overflow
    //     if (r_vec < 0 || r_vec > N - 1 || visited[r_vec][c_vec] == 1 ||
    //         c_vec < 0 || c_vec > M - 1 || visited[r_vec][c_vec] == 8)
    //         continue;

    //     // keep going straight or change direction
    //     if (!(i == directii[index] || i == directii[index + 1]))
    //         continue;

    //     { // test print before every new graph
    //         printf("| %d | Path: -> [%d %d], and directii: ", index, r_vec, c_vec);
    //         int all = index;
    //         do
    //         {
    //             printf("%d ", directii[all]);
    //             all++;
    //         } while (all < K);
    //         printf("\n");
    //     }

    //     visited[r_vec][c_vec] = 8;
    //     printGraph(visited, N, M);

    //     if (i == directii[index])
    //         solve(graph, visited, directii, index, N, M, K, r_vec, c_vec);

    //     if (i == directii[index + 1])
    //     {
    //         printf("new direction now: %d:\n", directii[index + 1]);
    //         index++;
    //         solve(graph, visited, directii, index, N, M, K, r_vec, c_vec);
    //     }

    // visited[r_vec][c_vec] = 0;
    // printf("---------------\n");
    // printGraph(visited, N, M);
    // }
    // printf("|||||||||||||||||||||||||||||||||||\n");
}