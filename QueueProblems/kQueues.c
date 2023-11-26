#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct kQueues {
    int k;
    int sizePerQueue;
    int totalSize;
    int* array;
    int* front;
    int* rear;
} kQueues;

kQueues* create_kQueues(int k, int sizePerQueue) {
    kQueues* kq = (kQueues*)malloc(sizeof(kQueues));
    kq->k = k;
    kq->sizePerQueue = sizePerQueue;
    kq->totalSize = k*sizePerQueue;
    kq->array = (int*)malloc(sizeof(int)*kq->totalSize);
    kq->front = (int*)malloc(sizeof(int)*k);
    kq->rear = (int*)malloc(sizeof(int)*k);
    for(int i = 0; i<k; i++) {
        kq->front[i] = -1;
        kq->rear[i] = -1;
    }
    return kq;
}

bool isQnFull(kQueues* queue, int qn) {
    if((qn*queue->sizePerQueue + (queue->rear[qn]+1)%queue->sizePerQueue)==queue->front[qn])
        return true;
    else
        return false;
}

bool isQnEmpty(kQueues* queue, int qn) {
    if(queue->front[qn]==-1 && queue->rear[qn]==queue->front[qn])
        return true;
    else
        return false;
}

void enqueue(kQueues* queue, int x, int qn) {
    if(isQnFull(queue, qn)) {
        printf("Queue %d is full\n", qn);
    }
    else {
        if(queue->front[qn]==-1) {
            queue->front[qn]++;
            queue->front[qn] = qn*queue->sizePerQueue + queue->front[qn]%queue->sizePerQueue;  
        }
        queue->rear[qn]++;
        queue->rear[qn] = qn*queue->sizePerQueue + queue->rear[qn]%queue->sizePerQueue;
        queue->array[queue->rear[qn]] = x;
    }
}

int dequeue(kQueues* queue, int qn) {
    if(isQnEmpty(queue, qn))
        printf("Queue %d is empty\n", qn);
    else {
        int popped = queue->array[queue->front[qn]];
        if(queue->front[qn]==queue->rear[qn]) {
            queue->front[qn] = queue->rear[qn] = -1;
        }
        else {
            queue->front[qn]++;
            queue->front[qn] = qn*queue->sizePerQueue + queue->front[qn]%queue->sizePerQueue; 
        }
        return popped;
    }
}

void displayq(kQueues* queue, int qn){
    if(isQnEmpty(queue, qn)) {
        printf("Queue %d is empty\n", qn);
    }
    else {
        printf("The Queue %d consists : \n", qn);
        printf("front-> [");
        int i;
        for(i = queue->front[qn]; i!=queue->rear[qn]; i = qn*queue->sizePerQueue + (i+1)%queue->sizePerQueue) {
            printf("%d, ", queue->array[i]);
        }
        printf("%d", queue->array[i]);
        printf("] <- rear\n");
    }
}

void displayAll(kQueues* queue) {
    for(int i = 0; i<queue->k; i++) {
        displayq(queue, i);
    }
}

