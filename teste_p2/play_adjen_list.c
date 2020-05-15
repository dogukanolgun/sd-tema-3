// Adjascency List representation in C

#include <stdio.h>
#include <stdlib.h>

struct Graph
{
    int numVertices;
    struct node **adjLists;
};

struct node
{
    int vertex;
    struct node *next;
};

struct node *createNode(int);
void printGraph(struct Graph *graph);
struct Graph *createGraph(int vertices);
void addEdge(struct Graph *graph, int src, int dest);

int main()
{
    struct Graph *graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 2);

    printGraph(graph);

    return 0;
}

// Create a graph
struct Graph *createGraph(int vertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = (struct node **)malloc(vertices * sizeof(struct node *));

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// Create a node
struct node *createNode(int v)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Add edge
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
        printf("wow\n");
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
        printf("wow\n");
        graph->adjLists[dest] = newNode;
    }
    else
    {
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Print the graph
void printGraph(struct Graph *graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node *temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}