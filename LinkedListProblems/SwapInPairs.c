#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

ListNode* create_node(int data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->val = data;
    node->next = NULL;
}

ListNode* swapPairs(ListNode* head) {
    if(head==NULL || head->next==NULL || head->next->next==NULL)
        return head;
    ListNode* prev = head->next;
    ListNode* curr = head->next->next;
    ListNode* ahead= head->next->next->next;
    head->next = curr;
    while(ahead!=NULL) {
        curr->next = prev;
        if(ahead->next!=NULL)
            prev->next = ahead->next;
        else
            prev->next = ahead;
        prev = ahead;
        curr = ahead->next;
        if(curr!=NULL)
            ahead = curr->next;
        else
            ahead = curr;
    }
    if(curr==NULL)
        return head; 
    curr->next = prev;
    prev->next = ahead;
    return head; 
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
    ListNode* node2 = create_node(6);
    ListNode* node3 = create_node(2);
    ListNode* node4 = create_node(5);
    ListNode* node5 = create_node(2);
    ListNode* node6 = create_node(3);
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = NULL;
    displayList(head);
    ListNode* newhead = swapPairs(head);
    displayList(newhead);
    return 0;
}