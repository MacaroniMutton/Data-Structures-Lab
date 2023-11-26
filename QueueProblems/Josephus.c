#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.c"

int findTheWinner(int n, int k) {
    Queue* queue = create_queue(n);
    for(int i = 1; i<=n; i++) {
        enqueue(queue, i);
    }
    int count = 1;
    while(front(queue)!=rear(queue)) {
        if(count < k) {
            enqueue(queue, dequeue(queue));
        }
        else {
            dequeue(queue);
            count = 0;
        }
        count++;
    }
    int winner = dequeue(queue);
    return winner;
}

int main() {
    int n = 6;
    int k = 2;
    printf("%d\n", findTheWinner(n, k));
    return 0;
}