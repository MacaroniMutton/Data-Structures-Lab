/*
 * File: expression_tree_postorder.c
 * Author: Siddhartha Chandra
 * Email: siddhartha_chandra@spit.ac.in
 * Created: October 17, 2023
 * Description: Create an expression tree from a postorder traversal. 
 *  Additionally, add function to evaluate a given expression tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "stack.c"
#include "Traversals.c"


// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to perform an operation on 2 operands
float perform_operation(char op, float left, float right){
    switch (op) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                if (right != 0) {
                    return left / right;
                } else {
                    fprintf(stderr, "Error: Division by zero\n");
                    exit(EXIT_FAILURE);
                }
            default:
                fprintf(stderr, "Error: Unknown operator %c\n", op);
                exit(EXIT_FAILURE);
        }
}


// TODO: To be completed
ExprTreeNode *create_node(OpType op_type, Data data){
    ExprTreeNode* node = (ExprTreeNode*)malloc(sizeof(ExprTreeNode));
    node->type = op_type;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
}


// TODO: To be completed
// NOTE: Use the stack 'display' in this function to display stack state right after a given character in the expression has been processed.
// Do this for all characters of the expression string
ExprTreeNode *create_ET_from_postfix(char *postfix_expression){
    Stack* stack = initialize_stack(strlen(postfix_expression));
    for(int i = 0; i<strlen(postfix_expression); i++) {
        if(isOperator(postfix_expression[i])) {
            Data data;
            data.operation = postfix_expression[i];
            ExprTreeNode* node = create_node(OPERATOR, data);
            ExprTreeNode* rightOp = pop(stack);
            ExprTreeNode* leftOp = pop(stack);
            node->left = leftOp;
            node->right = rightOp;
            push(stack, node);
        }
        else {
            Data data;
            data.operand = (postfix_expression[i] - 48);
            ExprTreeNode* node = create_node(OPERAND, data);
            push(stack, node);
        }
        display(stack);
    }
    ExprTreeNode* root = pop(stack);
    return root;
}


// TODO: To be completed
float evaluate_ET(ExprTreeNode* root){
    if(root->left==NULL && root->right==NULL)
        return root->data.operand;

    float leftVal = evaluate_ET(root->left);
    float rightVal = evaluate_ET(root->right);
    return perform_operation(root->data.operation, leftVal, rightVal);
}

int main() {
    // char* postfix = "52+31-*";
    char* postfix = "3462*+83-25-*4+*+26*-";
    ExprTreeNode* root = NULL;
    root = create_ET_from_postfix(postfix);
    printf("Level Order Traversal : \n");
    levelOrderTraversal(root);
    printf("\n");
    printf("Pre Order Traversal : \n");
    preOrderTraversal(root);
    printf("\n");
     printf("In Order Traversal : \n");
     inOrderTraversal(root);
     printf("\n");
    printf("Post Order Traversal : \n");
    postOrderTraversal(root);
    printf("\n");
    printf("\nOn evaluating the expression tree, we get: %.2f", evaluate_ET(root));

    return 0;
}
