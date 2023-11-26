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

ListNode* reverse(ListNode* head) {
    if(head==NULL || head->next==NULL || head->next->next==NULL)
        return head;
    ListNode* prev = head->next;
    ListNode* curr = prev->next;
    ListNode* ahead = curr->next;
    head->next->next = NULL;
    while(ahead!=NULL) {
        curr->next = prev;
        prev = curr;
        curr = ahead;
        ahead = ahead->next;
    }
    curr->next = prev;
    head->next = curr;
    return head;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    reverse(l1);
    reverse(l2);
    ListNode* ans = create_node(0);
    ListNode* anstemp = ans;
    ListNode* temp1 = l1->next;
    ListNode* temp2 = l2->next;
    int a = 0, b = 0, sum = 0, carry = 0;
    while(temp1!=NULL || temp2!=NULL) {
        if(temp1==NULL) 
            a = 0;
        else
            a = temp1->val;
        if(temp2==NULL)
            b = 0;
        else
            b = temp2->val;
        sum = a + b + carry;
        carry = sum / 10;
        sum = sum % 10;
        ListNode* newNode = create_node(sum);
        anstemp->next = newNode;
        anstemp = newNode;
        if(temp1!=NULL)
            temp1 = temp1->next;
        if(temp2!=NULL)
            temp2 = temp2->next;
    }
    if(carry!=0) {
        ListNode* newNode = create_node(carry);
        anstemp->next = newNode;
        anstemp = newNode;
    }
    reverse(ans);
    return ans;
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
    ListNode* l1 = create_node(0);
    ListNode* l1node1 = create_node(1);
    ListNode* l1node2 = create_node(6);
    ListNode* l1node3 = create_node(2);
    ListNode* l1node4 = create_node(5);
    ListNode* l1node5 = create_node(2);
    ListNode* l1node6 = create_node(3);
    l1->next = l1node1;
    l1node1->next = l1node2;
    l1node2->next = l1node3;
    l1node3->next = l1node4;
    l1node4->next = l1node5;
    l1node5->next = l1node6;
    l1node6->next = NULL;
    ListNode* l2 = create_node(0);
    ListNode* l2node1 = create_node(9);
    ListNode* l2node2 = create_node(3);
    ListNode* l2node3 = create_node(2);
    ListNode* l2node4 = create_node(7);
    ListNode* l2node5 = create_node(6);
    ListNode* l2node6 = create_node(2);
    l2->next = l2node1;
    l2node1->next = l2node2;
    l2node2->next = l2node3;
    l2node3->next = l2node4;
    l2node4->next = l2node5;
    l2node5->next = l2node6;
    l2node6->next = NULL;
    displayList(l1);
    displayList(l2);
    ListNode* result = addTwoNumbers(l1, l2);
    displayList(result);
    return 0;
}