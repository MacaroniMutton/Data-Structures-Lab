#include "stack.c"
#include <string.h>

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
            return left ^ right;
    }
}

int prefixEval(char* prefix) {
    Stack* st = create_stack(strlen(prefix));
    for(int i = strlen(prefix)-1; i>=0; i--) {
        if(prefix[i]==' ')
            continue;
        if(!is_operator(prefix[i])) {
            push(st, prefix[i]-'0');
        }
        else {
            int leftOp = (char)pop(st);
            int rightOp = (char)pop(st);
            char operator = prefix[i];
            int result = evaluate(leftOp, operator, rightOp);
            push(st, result);
        }
    }
    return pop(st);
}

int main() {
    char* prefixExp = "- + 2 * 3 1 9";
    printf("%d", prefixEval(prefixExp));
    return 0;
}