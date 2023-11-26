#include "stack.c"

typedef struct Queue {
    Stack* stack;
    Stack* reverse;
    int size;
} Queue;

Queue* create_queue(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->size = size;
    queue->stack = create_stack(size);
    queue->reverse = create_stack(size);
    return queue;
}

bool isQueueEmpty(Queue* queue) {
    if(isStackEmpty(queue->stack))
        return true;
    else
        return false;
}

bool isQueueFull(Queue* queue) {
    if(isStackFull(queue->stack))
        return true;
    else
        return false;
}

int front(Queue* queue) {
    if(isQueueEmpty(queue)) {
        printf("Queue is empty\n");
    }
    else {
        while(!isStackEmpty(queue->stack)) {
            push(queue->reverse, pop(queue->stack));
        }
        int fr = top(queue->reverse);
        while(!isStackEmpty(queue->reverse)) {
            push(queue->stack, pop(queue->reverse));
        }
        return fr;
    }
}

int rear(Queue* queue) {
    if(isQueueEmpty(queue)) {
        printf("Queue is empty\n");
    }
    else {
        int re = top(queue->stack);
        return re;
    }
}

void enqueue(Queue* queue, int node) {
    if(isQueueFull(queue))
        printf("Queue is full!\n");
    else {
        push(queue->stack, node);
    }
}

int dequeue(Queue* queue) {
    if(isQueueEmpty(queue))
        printf("Queue empty\n");
    else {
        while(!isStackEmpty(queue->stack)) {
            push(queue->reverse, pop(queue->stack));
        }
        int fr = pop(queue->reverse);
        while(!isStackEmpty(queue->reverse)) {
            push(queue->stack, pop(queue->reverse));
        }
        return fr;  
    }
}