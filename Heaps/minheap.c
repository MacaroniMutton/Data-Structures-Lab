#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct MinHeap {
    int* array;
    int size;
    int capacity;
} MinHeap;

MinHeap* create_maxheap(int capacity) {
    MinHeap* mh = (MinHeap*)malloc(sizeof(MinHeap));
    mh->array = (int*)malloc(sizeof(int)*(capacity+1));
    mh->capacity = capacity;
    mh->size = 0;
    return mh;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void deleteHeap(MinHeap* heap) {
    free(heap->array);
    free(heap);
    heap = NULL;
}

void insert(MinHeap* heap, int x) {
    if(heap->size==heap->capacity) {
        printf("Heap is full");
        return;
    }
    heap->size++;
    int i = heap->size;
    heap->array[i] = x;
    while(i>1 && heap->array[i] < heap->array[i/2]) {
        int temp = heap->array[i];
        heap->array[i] = heap->array[i/2];
        heap->array[i/2] = temp;
        i = i / 2;
    }
}

void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int leftChild = 2*i;
    int rightChild = 2*i+1;
    //To check if leftChild exists, check if leftChild is in array, ie, leftChild<=heap->size
    if(leftChild<=heap->size && heap->array[leftChild]<heap->array[smallest]) {
        smallest = leftChild;
    }
    //To check if rightChild exists, check if rightChild is in array, ie, rightChild<=heap->size
    if(rightChild<=heap->size && heap->array[rightChild]<heap->array[smallest]) {
        smallest = rightChild;
    }

    if(smallest!=i) {
        swap(&heap->array[smallest], &heap->array[i]);
        heapify(heap, smallest);
    }
}

int peekMin(MinHeap* heap) {
    if(heap->size==0) {
        printf("Heap is empty.");
    }
    else {
        return heap->array[1];
    }
}

int extractMin(MinHeap* heap) {
    if(heap->size==0) {
        printf("Heap is empty.");
    }
    else {
        int min = heap->array[1];
        swap(&heap->array[1], &heap->array[heap->size]);
        heap->size--;
        heapify(heap, 1);
        return min;
    }  
}

void display_heap(MinHeap* heap, int stop_idx) {
    for (int i = 1; i <= stop_idx; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

MinHeap* constructHeap(int* arr, int arr_length) {
    MinHeap* heap = create_maxheap(arr_length);
    heap->size = arr_length;
    for(int i = 0; i<arr_length; i++) {
        heap->array[i+1] = arr[i];
    }
    for(int i = heap->size/2; i>=1; i--) {
        heapify(heap, i);
    }
    return heap;
}

void heapSortDescending(MinHeap* heap) {
    for(int i = heap->size/2; i>=1; i--) {
        heapify(heap, i);
    }
    for(int i = heap->size; i>1; i--) {
        swap(&heap->array[1], &heap->array[i]);
        heap->size--;
        heapify(heap, 1);
    }
}

int main() {
    int arr[] = {1,4,3,6,7,4,3,2,2,1,8,7,9,9,7,6};
    int arr_length = sizeof(arr)/sizeof(int);
    MinHeap* heap = constructHeap(arr, arr_length);
    display_heap(heap, heap->size);
    heapSortDescending(heap);
    display_heap(heap, arr_length);
    return 0;
}

