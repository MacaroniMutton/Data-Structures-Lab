#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct PolyNode {
    int coeff;
    int power;
    struct PolyNode* next;
} PolyNode;

PolyNode* create_node(int coeff, int power) {
    PolyNode* node = (PolyNode*)malloc(sizeof(PolyNode));
    node->coeff = coeff;
    node->power = power;
    node->next = NULL;
}

void insert(PolyNode* head, int coeff, int power) {
    if(head==NULL) {
        head = create_node(0, 0);
    }
    PolyNode* newNode = create_node(coeff, power);
    if(head->next==NULL) {
        head->next = newNode;
    }
    else {
        PolyNode* curr = head->next;
        PolyNode* prev = NULL;
        while(curr!=NULL && curr->power>power) {
            prev = curr;
            curr = curr->next;
        }
        if(prev==NULL) {
            newNode->next = head->next;
            head->next = newNode;
        }
        else {
            prev->next = newNode;
            newNode->next = curr;
        }
    }
}

void display(PolyNode* head) {
    if(head==NULL || head->next==NULL) {
        printf("Empty");
        return;
    }
    PolyNode* temp = head->next;
    while(temp->next!=NULL) {
        if(temp->coeff==0) {
            temp = temp->next;
            continue;
        }
        printf("(%d)x^%d + ", temp->coeff, temp->power);
        temp = temp->next;
    }
    printf("(%d)x^%d\n", temp->coeff, temp->power);
}

PolyNode* addPoly(PolyNode* p1, PolyNode* p2) {
    PolyNode* temp1 = p1->next;
    PolyNode* temp2 = p2->next;
    PolyNode* ans = create_node(0, 0);
    PolyNode* anstemp = ans;
    while(temp1!=NULL || temp2!=NULL) {
        if(temp1==NULL) {
            anstemp->next = temp2;
            break;
        }
        if(temp2==NULL) {
            anstemp->next = temp1;
            break;
        }
        if(temp1->power>temp2->power) {
            PolyNode* newNode = create_node(temp1->coeff, temp1->power);
            anstemp->next = newNode;
            anstemp = newNode;
            temp1 = temp1->next;
        }
        else if(temp1->power<temp2->power) {
            PolyNode* newNode = create_node(temp2->coeff, temp2->power);
            anstemp->next = newNode;
            anstemp = newNode;
            temp2 = temp2->next;
        }
        else {
            PolyNode* newNode = create_node(temp1->coeff+temp2->coeff, temp2->power);
            anstemp->next = newNode;
            anstemp = newNode;
            temp1 = temp1->next;
            temp2 = temp2->next;    
        }
    }
    return ans;
}

int main() {
    PolyNode* p1 = create_node(0, 0);
    insert(p1, 2, 2);
    insert(p1, 3, 1);
    insert(p1, 7, 5);
    display(p1);
    PolyNode* p2 = create_node(0, 0);
    insert(p2, 6, 2);
    insert(p2, 3, 7);
    insert(p2, 2, 5);
    display(p2);
    PolyNode* sum = addPoly(p1, p2);
    display(sum);
}