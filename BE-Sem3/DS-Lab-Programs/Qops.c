#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct{
    int front, rear;
    int capacity;
    int *array;
} Queue;

Queue *createQueue(int capacity){
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    if (queue == NULL){
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    queue->capacity = capacity;
    queue->front = -1;
    queue->rear = -1;
    queue->array = (int *)malloc(capacity * sizeof(int));

    if (queue->array == NULL){
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    return queue;
}

int isEmpty(Queue *queue){
    return (queue->front == -1);
}

int isFull(Queue *queue){
    return ((queue->rear + 1) % queue->capacity == queue->front);
}

void enqueue(Queue *queue, int item){
    if (isFull(queue)){
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (isEmpty(queue)){
        queue->front = 0;
        queue->rear = 0;
    }

    else{
        queue->rear = (queue->rear + 1) % queue->capacity;
    }

    queue->array[queue->rear] = item;
    printf("Enqueued: %d\n", item);
}

int dequeue(Queue *queue){
    if (isEmpty(queue)){
        printf("Queue is empty. Cannot dequeue.\n");
        exit(EXIT_FAILURE);
    }

    int item = queue->array[queue->front];

    if (queue->front == queue->rear){
        queue->front = -1;
        queue->rear = -1;
    }

    else{
        queue->front = (queue->front + 1) % queue->capacity;
    }

    printf("Dequeued: %d\n", item);
    return item;
}

void display(Queue *queue){

    if (isEmpty(queue)){
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue: ");
    int i = queue->front;

    do{
        printf("%d ", queue->array[i]);
        i = (i + 1) % queue->capacity;
    } while (i != (queue->rear + 1) % queue->capacity);

    printf("\n");
}

void freeQueue(Queue *queue){
    free(queue->array);
    free(queue);
}

int main(){
    Queue *queue = createQueue(MAX_SIZE);

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);

    display(queue);

    dequeue(queue);
    dequeue(queue);

    display(queue);

    enqueue(queue, 60);

    display(queue);

    freeQueue(queue);

    return 0;
}
