/*
 * File: data_types.h
 * Author: Siddhartha Chandra
 * Email: siddhartha_chandra@spit.ac.in
 * Created: September 1, 2023
 * Description: This contains the ADTs for Stack and ExpressionTreeNode
 */


typedef union {
    char operation;
    float operand;
} Data; 

typedef enum {OPERATOR, OPERAND} OpType;

typedef struct ExprTreeNode{
    OpType type;
    Data data;
    struct ExprTreeNode *left;
    struct ExprTreeNode *right;
} ExprTreeNode;

ExprTreeNode *create_node(OpType op_type, Data data); 
ExprTreeNode *create_ET_from_postfix(char* postfix_expression);
float evaluate_ET(ExprTreeNode* exp_tree);


typedef struct Stack
{
    int top;
    unsigned size;
    ExprTreeNode** array;
} Stack;

void display(Stack* stack);
Stack* initialize_stack(unsigned size);
int isEmpty(Stack* stack);
void push(Stack *stack, ExprTreeNode *item);
void peek(Stack* stack);
ExprTreeNode *pop(Stack* stack);

