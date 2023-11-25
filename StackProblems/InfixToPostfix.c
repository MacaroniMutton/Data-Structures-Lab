#include "stack.c"
#include <string.h>

int op_prec(char op) {
    switch(op) {
        case '(':
        case ')':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

char* infixToPostfix(char* infix) {
    Stack* st = create_stack(strlen(infix));
    char* postfix = (char*)malloc(sizeof(char)*strlen(infix)+1);
    postfix[0] = '\0';
    for(int i = 0; infix[i]!='\0'; i++) {
        if(infix[i]=='(') {                                                 // If (, push in stack
            push(st, infix[i]);
        }
        else if(infix[i]==')') {
            while((char)top(st)!='(') {
                char popped = (char)pop(st);
                char tempstr[2] = {popped, '\0'};
                strcat(postfix, tempstr);
            }
            pop(st);
        }
        else if(op_prec(infix[i])==-1) {                                    // If operand is being read, store in postfix.
            char tempstr[2] = {infix[i], '\0'};
            strcat(postfix, tempstr);
        }
        else if(isStackEmpty(st) || op_prec(infix[i])>op_prec(top(st))) {   // If scanned operator has greater precedence than operator on top or stack is empty ,push in stack
            push(st, infix[i]);
        }
        else {                                                              //If scanned operator has prec lower than or equal to operator on top of stack ,pop top operator in postfix and push scanned operator in stack
            char tempstr[2] = {(char)pop(st), '\0'};
            strcat(postfix, tempstr);
            push(st, infix[i]);
        }
    }
    while (!isStackEmpty(st)) {
        char popped = (char)pop(st);
        if (op_prec(popped) >= 1) {
            char tempstr[2] = {popped, '\0'};
            strcat(postfix, tempstr);
        }
    }
    return postfix;
}

int main() {
    char* infix = "(a+b-c)*d-(e+f)";
    char* postfix = infixToPostfix(infix);
    printf("%s", postfix);
    return 0;
}