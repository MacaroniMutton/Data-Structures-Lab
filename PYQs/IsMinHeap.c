#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isMinHeap(int arr[], int n, int i) {
    if(i>=n/2)
        return true;
    
    int leftChild = 2*i+1;
    int rightChild = 2*i+2;

    if((leftChild<n && arr[i]>arr[leftChild]) || (rightChild<n && arr[i]>arr[rightChild]))
        return false;

    return isMinHeap(arr, n, leftChild) && isMinHeap(arr, n, rightChild);
}

int main() {
    int arr[] = {2, 3, 5, 7, 8, 10};
    int n = sizeof(arr)/sizeof(arr[0]);
    if(isMinHeap(arr, n, 0)) {
        printf("Min Heap\n");
    }
    else {
        printf("Not a Min Heap\n");
    }
    return 0;
}