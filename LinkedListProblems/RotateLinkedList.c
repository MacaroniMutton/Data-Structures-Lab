#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

ListNode* create_node(int data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->val = data;
    node->next = NULL;
}

ListNode* rotateRight(ListNode* head, int k) {
    if(k==0 || head==NULL || head->next==NULL || head->next->next==NULL)
        return head;
    ListNode* temp = head->next;
    int n = 0;
    while(temp!=NULL) {
        n++;
        temp = temp->next;
    }
    if(k==n)
        return head;
    k=k%n;
    temp = head->next;
    int i = 1;
    while(i<n-k) {
        temp = temp->next;
        i++;
    }
    ListNode* newhead = create_node(0);
    newhead->next = temp->next;
    temp->next = NULL;
    temp = newhead;
    while(temp->next!=NULL) {
        temp = temp->next;
    }
    temp->next = head->next;
    return newhead;
}

void displayList(ListNode* head) {
    ListNode* temp = head->next;
    while(temp->next!=NULL) {
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("%d\n", temp->val);
}

int main() {
    ListNode* head = create_node(0);
    ListNode* node1 = create_node(1);
    ListNode* node2 = create_node(2);
    ListNode* node3 = create_node(3);
    ListNode* node4 = create_node(4);
    ListNode* node5 = create_node(5);
    ListNode* node6 = create_node(6);
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = NULL;
    displayList(head);
    ListNode* newhead = rotateRight(head, 13);
    displayList(newhead);
    return 0;
}