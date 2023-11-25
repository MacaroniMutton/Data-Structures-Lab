
#include <string.h>
#include "ReverseString.c"

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

char* infixToPrefix(char* infix) {
    Stack* st = create_stack(strlen(infix));
    char* prefix = (char*)malloc(sizeof(char)*strlen(infix)+1);
    prefix[0] = '\0';
    for(int i = strlen(infix)-1; i>=0; i--) {
        if(infix[i]==')') {                                                 // If ), push in stack
            push(st, infix[i]);
        }
        else if(infix[i]=='(') {                                            // If (, keep popping till ) encountered.
            while((char)top(st)!=')') {
                char popped = (char)pop(st);
                char tempstr[2] = {popped, '\0'};
                strcat(prefix, tempstr);
            }
            pop(st);
        }
        else if(op_prec(infix[i])==-1) {                                    // If operand is being read, store in postfix.
            char tempstr[2] = {infix[i], '\0'};
            strcat(prefix, tempstr);
        }
        else if(isStackEmpty(st) || op_prec(infix[i])>op_prec(top(st))) {   // If scanned operator has greater precedence than operator on top or stack is empty ,push in stack
            push(st, infix[i]);
        }
        else {                                                              //If scanned operator has prec lower than or equal to operator on top of stack ,pop top operator in postfix and push scanned operator in stack
            char tempstr[2] = {(char)pop(st), '\0'};
            strcat(prefix, tempstr);
            push(st, infix[i]);
        }
    }
    while (!isStackEmpty(st)) {
        char popped = (char)pop(st);
        if (op_prec(popped) >= 1) {
            char tempstr[2] = {popped, '\0'};
            strcat(prefix, tempstr);
        }
    }
    return reverse(prefix);
}

int main() {
    char* infix = "4*(2-(6*3+4)*2)+1";
    char* prefix = infixToPrefix(infix);
    printf("%s", prefix);
    return 0;
}