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

ListNode* partition(ListNode* head, int x) {
    if(head==NULL || head->next==NULL)
        return head;
    ListNode* temp = head->next;
    ListNode* newhead = create_node(0);
    ListNode* end = newhead;
    int Xcount = 0;
    while(temp!=NULL) {
        if(temp->val==x) {
            Xcount++;
        }
        if(temp->val<x) {
            ListNode* newNode = create_node(temp->val);
            end->next = newNode;
            end = newNode;
        }
        temp = temp->next;
    }
    for(int i = 0; i<Xcount; i++) {
        ListNode* newNode = create_node(x);
        end->next = newNode;
        end = newNode;
    }
    temp = head->next;
    while(temp!=NULL) {
        if(temp->val>x) {
            ListNode* newNode = create_node(temp->val);
            end->next = newNode;
            end = newNode;
        }
        temp = temp->next;
    }
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
    ListNode* newhead = partition(head, 3);
    displayList(newhead);
    return 0;
}