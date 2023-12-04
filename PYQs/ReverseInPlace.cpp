#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

//Since question says to take a pointer to the beginning of LL
// We cannot make head as a separate node
//We need to keep head as pointer
//We'll need to use double pointer to make sure changes made to head in reverse are also reflected in main
//Should not use additional space, means we cannot create a new LL
// The original LL should be reversed.

void reverse(Node** head) {
    if((*head)==NULL || (*head)->next==NULL)
        return;
    Node* prev = *head;
    Node* curr = prev->next;
    Node* ahead = curr->next;
    prev->next = NULL;
    while(ahead!=NULL) {
        curr->next = prev;
        prev = curr;
        curr = ahead;
        ahead = ahead->next;
    }
    curr->next = prev;
    (*head) = curr;
}

void display(Node** head) {
    if((*head)==NULL)
        return;
    Node* temp = (*head);
    while(temp->next!=NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);
}

int main() {
    Node* n1 = NULL;
    Node* anode1 = create_node(1);
    Node* anode2 = create_node(2);
    Node* anode3 = create_node(3);
    Node* anode4 = create_node(4);
    Node* anode5 = create_node(5);
    n1 = anode1;
    anode1->next = anode2;
    anode2->next = anode3;
    anode3->next = anode4;
    anode4->next = anode5;
    anode5->next = NULL;
    display(&n1);
    reverse(&n1);
    display(&n1);

    return 0;
}