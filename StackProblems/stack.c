#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Stack {
    int* array;
    int top;
    int size;
} Stack;

Stack* create_stack(int size){
    Stack* st = (Stack*)malloc(sizeof(Stack));
    st->array = (int*)malloc(size*sizeof(int));
    st->size = size;
    st->top = -1;
    return st;
}

bool isStackFull(Stack* st) {
    if(st->top==st->size-1)
        return true;
    else
        return false;
}

bool isStackEmpty(Stack* st) {
    if(st->top==-1)
        return true;
    else
        return false;
}

void push(Stack* st, int n) {
    if(isStackFull(st)) {
        printf("Stack is full!\n");
    }
    else {
        st->top++;
        st->array[st->top] = n;
    }
}

int pop(Stack* st) {
    if(isStackEmpty(st)) {
        printf("Stack is empty\n");
    }
    else {
        int popped = st->array[st->top];
        st->top--;
        return popped;
    }
}

int top(Stack* st) {
    return st->array[st->top];
}