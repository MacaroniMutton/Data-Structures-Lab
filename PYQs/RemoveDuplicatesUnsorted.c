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

bool isPresentIn(Node* head, int data) {
    if(head==NULL || head->next==NULL)
        return false;
    Node* temp = head->next;
    while(temp!=NULL) {
        if(temp->data==data) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

Node* rmvDuplicates(Node* head) {
    if(head==NULL)
        return NULL;
    Node* temp = head->next;
    Node* newhead = create_node(0);
    Node* newtemp = newhead;
    while(temp!=NULL) {
        if(!isPresentIn(newhead, temp->data)) {
            Node* newNode = create_node(temp->data);
            newtemp->next = newNode;
            newtemp = newNode; 
        }
        temp = temp->next;
    }
    return newhead;
}

void display(Node* head) {
    if(head==NULL || head->next==NULL)
        return;
    Node* temp = head->next;
    while(temp->next!=NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);
}

int main() {
    Node* n1 = create_node(0);
    Node* anode1 = create_node(1);
    Node* anode2 = create_node(2);
    Node* anode3 = create_node(5);
    Node* anode4 = create_node(2);
    Node* anode5 = create_node(5);
    Node* anode6 = create_node(2);
    Node* anode7 = create_node(5);
    Node* anode8 = create_node(4);
    Node* anode9 = create_node(1);
    Node* anode10 = create_node(1);
    n1->next = anode1;
    anode1->next = anode2;
    anode2->next = anode3;
    anode3->next = anode4;
    anode4->next = anode5;
    anode5->next = anode6;
    anode6->next = anode7;
    anode7->next = anode8;
    anode8->next = anode9;
    anode9->next = anode10;
    anode10->next = NULL;
    display(n1);
    Node* n2 = rmvDuplicates(n1);
    display(n2);
    return 0;
}