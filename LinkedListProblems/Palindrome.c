#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
}

Node* reverse(Node* head) {
    if(head==NULL)
        return NULL;
    Node* newhead = create_node(0);         //newhead->data stores the length of the linked list
    Node* temp = head->next;
    while(temp!=NULL) {
        Node* newNode = create_node(temp->data);
        newNode->next = newhead->next;
        newhead->next = newNode;
        newhead->data++;
        temp = temp->next;
    }
    return newhead;
}

bool isPalindrome(Node* head) {
    Node* newhead = reverse(head);
    Node* temp1 = newhead->next;
    Node* temp2 = head->next;
    while(temp1!=NULL) {
        if(temp1->data!=temp2->data) {
            return false;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}

int main() {
    Node* head = create_node(0);
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    Node* node3 = create_node(3);
    Node* node4 = create_node(3);
    Node* node5 = create_node(2);
    Node* node6 = create_node(1);
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = NULL;
    if(isPalindrome(head)) {
        printf("Palindrome\n");
    }
    else {
        printf("Not Palindrome\n");
    }
    return 0;
}