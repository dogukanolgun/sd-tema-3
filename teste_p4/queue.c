// A C program to demonstrate linked list based implementation of queue
#include <stdio.h>
#include <stdlib.h>

// A linked list (LL) node to store a queue entry
struct QNode
{
    int value;
    struct QNode *next;
};

// The queue, front stores the front node of LL and rear stores the
// last node of LL
struct Queue
{
    struct QNode *front;
    struct QNode *rear;
};

// A utility function to create a new linked list node.
struct QNode *newNode(int val)
{
    struct QNode *temp = (struct QNode *)malloc(sizeof(struct QNode));
    temp->value = val;
    temp->next = NULL;
    return temp;
}

// A utility function to create an empty queue
struct Queue *createQueue()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

// The function to add a key k to q
void enQueue(struct Queue *q, int val)
{
    // Create a new LL node
    struct QNode *temp = newNode(val);

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

// Function to remove a key from given queue q
void deQueue(struct Queue *q, int *returned_val)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
    {
        *returned_val = -1;
        return;
    }
    *returned_val = q->front->value;

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
        printf("Queue is empty!\n");
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
    printf("works\n");
    if (q->rear == NULL && q->front == NULL)
    {
        printf("Queue empty!\n");
        return 1;
    }
    return 0;
}

// Driver Program to test anove functions
int main()
{
    int rtn;
    struct Queue *q = createQueue();

    // printQueue(q);
    // enQueue(q, 10);
    // printQueue(q);
    // enQueue(q, 20);
    // printQueue(q);
    // deQueue(q, &rtn);
    // printQueue(q);
    // enQueue(q, 30);
    // printQueue(q);
    // enQueue(q, 40);
    // printQueue(q);
    // enQueue(q, 50);
    // printQueue(q);
    // deQueue(q, &rtn);
    // printQueue(q);

    if (isEmptyQueue(q))
        printf("EMPTY\n");
    printQueue(q);
    // printf("Queue Front: %d\n", q->front->value);
    // printf("Queue Rear: %d\n", q->rear->value);

    freeQueue(q);
    return 0;
}
