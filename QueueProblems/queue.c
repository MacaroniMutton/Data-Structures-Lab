#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Queue {
    int* array;
    int size;
    int front;
    int rear;
} Queue;

Queue* create_queue(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->size = size;
    queue->array = (int*)malloc(sizeof(int)*size);
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

bool isQueueEmpty(Queue* queue) {
    if(queue->front==queue->rear && queue->front==-1)
        return true;
    else
        return false;
}

bool isQueueFull(Queue* queue) {
    if((queue->rear+1)%queue->size==queue->front)
        return true;
    else
        return false;
}

int front(Queue* queue) {
    if(queue->front==-1)
        printf("Queue empty\n");
    else
        return queue->array[queue->front];
}

int rear(Queue* queue) {
    if(queue->rear==-1)
        printf("Queue empty\n");
    else
        return queue->array[queue->rear];
}

void enqueue(Queue* queue, int node) {
    if(isQueueFull(queue))
        printf("Queue is full!\n");
    else {
        if(queue->front==-1) {
            queue->front++;
            queue->front %= queue->size;
        }
        queue->rear++;
        queue->rear %= queue->size;
        queue->array[queue->rear] = node;
    }
}

int dequeue(Queue* queue) {
    if(isQueueEmpty(queue))
        printf("Queue empty\n");
    else {
        int popped = queue->array[queue->front];
        if(queue->front==queue->rear) {
            queue->front = queue->rear = -1;
        }
        else {
            queue->front++;
            queue->front %= queue->size;
        }
        return popped;
    }
}