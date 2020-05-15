// BFS algorithm in C

#include <stdio.h>
#include <stdlib.h>
#define SIZE 40

struct queue
{
    int *items;
    int front;
    int rear;
};

struct node
{
    int vertex;
    struct node *next;
};

struct Graph
{
    int numVertices;
    struct node **adjLists;
    int *visited;
};

void enqueue(struct queue *q, int vertices, int value);
int dequeue(struct queue *q);
void display(struct queue *q);
int isEmpty(struct queue *q);
void printQueue(struct queue *q);

struct queue *createQueue(int vertices);
struct node *createNode(int v);
struct Graph *createGraph(int vertices);
void printGraph(struct Graph *graph);

void bfs(struct Graph *graph, int startVertex);
void addEdge(struct Graph *graph, int src, int dest);

int main()
{
    struct Graph *graph = createGraph(5);
    addEdge(graph, 0, 4);
    addEdge(graph, 0, 3);
    addEdge(graph, 0, 2);
    addEdge(graph, 2, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    printGraph(graph);

    bfs(graph, 0);

    return 0;
}

void bfs(struct Graph *graph, int startVertex)
{
    struct queue *q = createQueue(graph->numVertices);

    graph->visited[startVertex] = 1;
    enqueue(q, graph->numVertices, startVertex);

    while (!isEmpty(q))
    {
        printQueue(q);
        int currentVertex = dequeue(q);
        printf("Visited %d\n", currentVertex);

        printf("== visited Arr: ");
        for (int i = 0; i < graph->numVertices; i++)
            printf("%d ", graph->visited[i]);
        printf("\n\n");

        struct node *temp = graph->adjLists[currentVertex];

        while (temp)
        {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0)
            {
                graph->visited[adjVertex] = 1;
                enqueue(q, graph->numVertices, adjVertex);
            }
            temp = temp->next;
        }
    }
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
    graph->visited = (int *)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

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
        graph->adjLists[src] = newNode;
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
        graph->adjLists[dest] = newNode;
    else
    {
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

struct queue *createQueue(int vertices)
{
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    q->items = (int *)malloc(vertices * sizeof(int));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct queue *q)
{
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

void enqueue(struct queue *q, int vertices, int value)
{
    if (q->rear == vertices - 1)
        printf("\nQueue is Full!!");
    else
    {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct queue *q)
{
    int item;
    if (isEmpty(q))
    {
        printf("Queue is empty");
        item = -1;
    }
    else
    {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear)
        {
            printf("Resetting queue ");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct queue *q)
{
    int i = q->front;

    if (isEmpty(q))
    {
        printf("Queue is empty");
    }
    else
    {
        printf("Queue contains:");
        for (i = q->front; i < q->rear + 1; i++)
        {
            printf(" %d", q->items[i]);
        }
        printf("\n");
    }
}

void printGraph(struct Graph *graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node *temp = graph->adjLists[v];
        printf("| %d |", v);
        while (temp)
        {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}