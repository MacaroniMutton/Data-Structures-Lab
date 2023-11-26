#include "queue.c"
#include "stack.c"

void interleave(Queue* queue) {
    Stack* stack = create_stack(queue->size);
    for(int i = 0; i<queue->size/2; i++) {
        push(stack, dequeue(queue));
    }
    while(!isStackEmpty(stack)) {
        enqueue(queue, pop(stack));
    }
    for(int i = 0; i<queue->size/2; i++) {
        enqueue(queue, dequeue(queue));
    }
    for(int i = 0; i<queue->size/2; i++) {
        push(stack, dequeue(queue));
    }
    while(!isStackEmpty(stack)) {
        enqueue(queue, pop(stack));
        enqueue(queue, dequeue(queue));
    }
}

int main() {
    Queue* queue = create_queue(6);
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    enqueue(queue, 6);
    interleave(queue);
    while(!isQueueEmpty(queue)) {
        printf("%d\n", dequeue(queue));
    }
    return 0;
}