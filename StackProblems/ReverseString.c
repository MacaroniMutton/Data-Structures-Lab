#include "stack.c"
#include <string.h>

char* reverse(char* str) {
    Stack* st = create_stack(strlen(str));
    char* rev = (char*)malloc((strlen(str)+1)*sizeof(char));
    rev[0] = '\0';
    for(int i = 0; i<strlen(str); i++) {
        push(st, str[i]);
    }
    while(!isStackEmpty(st)) {
        char c[2] = {(char)pop(st), '\0'};
        strcat(rev, c);
    }
    free(st);
    return rev;
}

// int main() {
//     printf("%s", reverse("abcdefghijk000"));
//     return 0;
// }