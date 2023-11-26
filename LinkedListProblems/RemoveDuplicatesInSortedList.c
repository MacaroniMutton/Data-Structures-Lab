#include <stdlib.h>
#include <stdio.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

ListNode* create_node(int data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->val = data;
    node->next = NULL;
}

ListNode* deleteDuplicates(ListNode* head) {
    if(head==NULL || head->next==NULL || head->next->next==NULL)
        return head;
    ListNode* temp1 = head->next;
    ListNode* temp2 = head->next->next;
    while(temp2!=NULL) {
        if(temp1->val!=temp2->val) {
            temp1->next = temp2;
            temp1 = temp2;
        }
        temp2 = temp2->next;
    }
    temp1->next = temp2;
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
    ListNode* node2 = create_node(2);
    ListNode* node3 = create_node(2);
    ListNode* node4 = create_node(3);
    ListNode* node5 = create_node(3);
    ListNode* node6 = create_node(3);
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = NULL;
    displayList(head);
    ListNode* newhead = deleteDuplicates(head);
    displayList(newhead);
    return 0;
}