/*
 * File: stack.c
 * Author: Siddhartha Chandra
 * Email: siddhartha_chandra@spit.ac.in
 * Created: September 1, 2023
 * Description: This program implements a Stack ADT
 */

#include<stdio.h>
#include<stdlib.h>
#include "data_types.h"

// Build a Stack Abstract Data structure and perform operations on it 
// Operations:
// 1. Push
// 2. Pop
// 3. Peek
// 4. isEmpty
// 5. isFull
// 6. display


// 0 -> display
// Credit: containerized styling => |Manan Kher | SE Comps - A | Batch - 2026|
void display(Stack* stack){
    char displayed_val[10];
    if (stack->top == -1)
    {   
        printf("Nothing to display\n\n");
        return;
    }
        
    for (int i=stack->top; i>=0; i--){
        ExprTreeNode* element = stack->array[i];
        if (element->type == OPERAND)
            sprintf(displayed_val, "%.2f ", element->data.operand);
        else
            sprintf(displayed_val, "< %c >", element->data.operation);
        
        if (i == stack->top)
            printf("|  %s  | <-- top\n", displayed_val);
        else
            printf("|  %s  |\n", displayed_val);
    }
    printf("-----------\n\n");
}

// 1 -> Initialize
Stack* initialize_stack(unsigned size){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->size = size;
    stack->top = -1;
    stack->array = (ExprTreeNode **)malloc(stack->size * sizeof(ExprTreeNode *));
    return stack;
}

// 2 -> isFull
int isEmpty(struct Stack* stack){
    return stack->top == -1;
}

// 3 -> isEmpty
int isFull(Stack* stack){
    return stack->top == stack->size - 1;
}

// 4 -> push
void push(Stack *stack, ExprTreeNode *item){
    if (isFull(stack)){
        printf("Error: Stack is already full!\n");
    }
    else{
        stack->top += 1;
        stack->array[stack->top] = item;    
    }
    
}

// 5 -> peek
void peek(Stack* stack){
    char top_elem[10]; 
    if (isEmpty(stack)) {
        printf("Error: Stack is empty!\n");
    }
    else{
        ExprTreeNode *element = stack->array[stack->top];
        printf("Top element is: ");
        if (element->type == OPERAND)
            sprintf(top_elem, "%f", element->data.operand);
        else
            sprintf(top_elem, "%c", element->data.operation);
        
        printf("%s", top_elem);
        printf("\n\n");
    }
    
}

// 6 -> pop
ExprTreeNode *pop(Stack* stack){
    char top_elem[10]; 
    if (isEmpty(stack)) {
        printf("Error: Stack is empty!\n");
        return NULL;
    }
    else {
        ExprTreeNode *element = stack->array[stack->top];
        printf("Popped element is: ");

        if (element->type == OPERAND)
            sprintf(top_elem, "%.2f", element->data.operand);
        else
            sprintf(top_elem, "%c", element->data.operation);

        printf("%s", top_elem);
        printf("\n\n");
        stack->top -= 1;
        return element;
    }
}









