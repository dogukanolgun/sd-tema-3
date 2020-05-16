#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct QNode
{
    int value;
    int index;
    struct QNode *next;
};
struct Queue
{
    struct QNode *front;
    struct QNode *rear;
};
struct QNode *newNode(int val, int index);
struct Queue *createQueue();
void enQueue(struct Queue *q, int val, int index);
void deQueue(struct Queue *q, int *returned_val, int *returned_index);
void printQueue(struct Queue *q);
void freeQueue(struct Queue *q);
int isEmptyQueue(struct Queue *q);

struct node
{
    int vertex, weight;
    struct node *next;
};
struct Graph
{
    int numVertices;
    struct node **adjLists;
};
struct node *createNode(int, int wight);
struct Graph *createGraph(int vertices);
void addEdge(struct Graph *graph, int src, int dest, int weight);
void printGraph(struct Graph *graph);
void solve(struct Graph *graph, struct Queue *q, int *directii,
           int Q, int index, int vertices, int *solution);

int main(int argc, char *argv[])
{
    if (argc != 2) // check input format
    {
        printf("Incorrect format.\n");
        return 0;
    }
    int N, M, Q, u, v, x, starting_point, graph_size = 0, src, des;
    char filename[100];
    strcpy(filename, argv[1]);
    FILE *myFile = fopen(filename, "r");
    fscanf(myFile, "%d %d %d", &N, &M, &Q);
    printf("%d %d %d\n", N, M, Q);

    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        matrix[i] = (int *)malloc(M * sizeof(int));

    for (int i = 0; i < N; i++) // read matrix
        for (int j = 0; j < M; j++)
        {
            fscanf(myFile, "%d", &x);
            if (x == 0)
                graph_size++;
            if (x == 1)
                x = -1;
            if (x == 2)
                x = -2;
            matrix[i][j] = x;
        }
    for (int i = 0; i < N; i++) // print matrix
    {
        for (int j = 0; j < M; j++)
            printf("%2d ", matrix[i][j]);
        printf("\n");
    }

    int counter = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (matrix[i][j] == -1)
                continue;
            if (matrix[i][j] == -2)
                starting_point = counter;
            matrix[i][j] = counter;
            counter++;
        }
    }
    printf("Starting Point: %d\n", starting_point);

    for (int i = 0; i < N; i++) // print matrix
    {
        for (int j = 0; j < M; j++)
            printf("%2d ", matrix[i][j]);
        printf("\n");
    }

    struct Graph *graph = createGraph(graph_size + 1);

    for (int i = 0; i < N; i++) // CREATE GRAPH NODES = 0:graph_size-1
        for (int j = 0; j < M; j++)
        {
            if (matrix[i][j] == -1)
                continue;
            // if (matrix[i][j] == 6)
            //     continue;
            if (i - 1 >= 0 && matrix[i - 1][j] != -1)
                addEdge(graph, matrix[i][j], matrix[i - 1][j], 0);
            if (i + 1 < N && matrix[i + 1][j] != -1)
                addEdge(graph, matrix[i][j], matrix[i + 1][j], 1);
            if (j - 1 >= 0 && matrix[i][j - 1] != -1)
                addEdge(graph, matrix[i][j], matrix[i][j - 1], 2);
            if (j + 1 < M && matrix[i][j + 1] != -1)
                addEdge(graph, matrix[i][j], matrix[i][j + 1], 3);

            // printf("[%d %d]\n", i, j);
        }

    int *directii = (int *)calloc(Q, sizeof(int));
    for (int i = 0; i < Q; i++)
        fscanf(myFile, "%d", &directii[i]);
    for (int i = 0; i < Q; i++)
        printf("%d ", directii[i]);
    printf("\n");

    printGraph(graph);
    int index = 0, solution = 0;
    struct Queue *q = createQueue();
    enQueue(q, starting_point, 0);
    // enQueue(q, 11, 2);
    // enQueue(q, 7, 2);
    // enQueue(q, 4, 2);
    solve(graph, q, directii, Q, index, counter - 1, &solution);
    freeQueue(q);
    printf("| -> %d <- |\n", solution);
}

void solve(struct Graph *graph, struct Queue *q, int *directii,
           int Q, int index, int vertices, int *solution)
{
    printf("===========%d=============\n", Q);
    while (!isEmptyQueue(q))
    {
        int start, index;
        deQueue(q, &start, &index);

        // printGraph(graph);
        // printf("Starting Point: %d\nVertices: %d\n", start, vertices);
        // printf("||| Index: %d |||\n", index);

        int next_dir = directii[index];
        struct node *temp = graph->adjLists[start];
        while (temp->weight != next_dir && temp->next != NULL)
            temp = temp->next;

        while (temp->weight == next_dir)
        {
            // printf("[%d %d] Dir: %d\n", temp->vertex, temp->weight, next_dir);
            if (index < Q - 1)
                // printf("\n\n|||||||||\n\n");
                enQueue(q, temp->vertex, index + 1);
            // else
            //     (*solution)++;
            if (index == Q - 1)
                (*solution)++;

            temp = graph->adjLists[temp->vertex];
            while (temp->weight != next_dir && temp->next != NULL)
                temp = temp->next;
        }
        // printQueue(q);
    }
}
struct node *createNode(int v, int weight)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->weight = weight;
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
void addEdge(struct Graph *graph, int src, int dest, int weight)
{
    // Add edge from src to dest
    //    //   struct node* newNode = createNode(dest);
    //    //   newNode->next = graph->adjLists[src];
    //    //   graph->adjLists[src] = newNode;
    struct node *newNode = createNode(dest, weight);
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

    // // Add edge from dest to src
    // //     // newNode = createNode(src);
    // //     // newNode->next = graph->adjLists[dest];
    // //     // graph->adjLists[dest] = newNode;
    // newNode = createNode(src);
    // temp = graph->adjLists[dest];
    // if (graph->adjLists[dest] == NULL)
    // {
    //     // printf("wow\n");
    //     graph->adjLists[dest] = newNode;
    // }
    // else
    // {
    //     while (temp->next)
    //         temp = temp->next;
    //     temp->next = newNode;
    // }
}
void printGraph(struct Graph *graph)
{
    for (int v = 0; v < graph->numVertices; v++)
    {
        struct node *temp = graph->adjLists[v];
        printf("|| %d || ", v);
        while (temp)
        {
            printf("->  %d", temp->vertex);
            printf("[%d] ", temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

struct QNode *newNode(int val, int index)
{
    struct QNode *temp = (struct QNode *)malloc(sizeof(struct QNode));
    temp->value = val;
    temp->index = index;
    temp->next = NULL;
    return temp;
}
struct Queue *createQueue()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}
void enQueue(struct Queue *q, int val, int index)
{
    // Create a new LL node
    struct QNode *temp = newNode(val, index);

    // If queue is empty, then new node is front and rear both
    if (q->rear == NULL)
    {
        q->front = temp;
        q->rear = temp;
        return;
    }

    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
}
void deQueue(struct Queue *q, int *returned_val, int *returned_index)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
    {
        *returned_val = -1;
        *returned_index = -1;
        return;
    }
    *returned_val = q->front->value;
    *returned_index = q->front->index;

    // Store previous front and move front one node ahead
    struct QNode *temp = q->front;

    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}
void printQueue(struct Queue *q)
{
    if (q->rear == NULL)
    {
        printf("Queue: empty\n");
        return;
    }

    if (q->rear == q->front)
    {
        printf("Queue: %d\n", q->front->value);
        return;
    }

    struct QNode *temp = q->front;

    printf("Queue: %d", temp->value);
    while (temp->next != NULL)
    {
        temp = temp->next;
        printf(" -> %d", temp->value);
    }
    printf("\n");
}
void freeQueue(struct Queue *q)
{
    if (q->rear == NULL)
    {
        printf("Queue is already empty!\n");
        return;
    }

    if (q->rear == q->front)
    {
        free(q->rear);
        return;
    }

    struct QNode *temp = q->front;

    while (temp->next->next != NULL)
    {
        temp = temp->next;
        q->front->next = q->front->next->next;
        free(temp);
    }
    free(temp->next);
    free(temp);
    free(q);
}
int isEmptyQueue(struct Queue *q)
{
    //     printf("works\n");
    if (q->rear == NULL && q->front == NULL)
    {
        // printf("Queue empty!\n");
        return 1;
    }
    return 0;
}