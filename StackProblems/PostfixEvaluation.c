#include "stack.c"
#include <string.h>
#include <math.h>

bool is_operator(char op) {
    switch(op) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return true;
        default:
            return false;
    }
}

int evaluate(int left, char operator, int right) {
    switch(operator) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
        case '^':
            return pow(left, right);
    }
}

int postfixEval(char* postfix) {
    Stack* st = create_stack(strlen(postfix));
    for(int i = 0; i<strlen(postfix); i++) {
        if(postfix[i]==' ')
            continue;
        if(!is_operator(postfix[i])) {
            push(st, postfix[i]-'0');
        }
        else {
            int rightOp = (char)pop(st);
            int leftOp = (char)pop(st);
            char operator = postfix[i];
            int result = evaluate(leftOp, operator, rightOp);
            push(st, result);
        }
    }
    return pop(st);
}

int main() {
    char* postfixExp = "2 3 1 * + 9 -";
    printf("%d", postfixEval(postfixExp));
    return 0;
}