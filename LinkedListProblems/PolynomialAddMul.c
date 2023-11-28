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

PolyNode* deleteDuplicates(PolyNode* head) {
    if(head==NULL || head->next==NULL || head->next->next==NULL)
        return head;
    PolyNode* temp1 = head->next;
    PolyNode* temp2 = head->next->next;
    int sum = temp1->coeff;
    while(temp2!=NULL) {
        if(temp1->power!=temp2->power) {
            temp1->next = temp2;
            temp1->coeff = sum;
            temp1 = temp2;
            sum = temp1->coeff;
            temp2 = temp2->next;
            continue;
        }
        sum += temp2->coeff;
        temp2 = temp2->next;
    }
    temp1->next = temp2;
    temp1->coeff = sum;
    return head;
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
    deleteDuplicates(head);
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

int swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sort(PolyNode* head) {
    int n = 0;
    PolyNode* temp = head->next;
    while(temp!=NULL) {
        n++;
        temp = temp->next;
    }
    for(int i = 0; i<n-1; i++) {
        PolyNode* tempj = head->next;
        for(int j = 0; j<n-1-i; j++) {
            PolyNode* node1 = tempj;
            PolyNode* node2 = tempj->next;
            if(node1->power<node2->power) {
                swap(&node1->power, &node2->power);
                swap(&node1->coeff, &node2->coeff);
            }
            tempj = tempj->next;
        }
    }
}



PolyNode* multiplyPoly(PolyNode* p1, PolyNode* p2) {
    PolyNode* ans = create_node(0, 0);
    PolyNode* anstemp = ans;
    PolyNode* temp1 = p1->next;
    while(temp1!=NULL) {
        PolyNode* temp2 = p2->next;
        while(temp2!=NULL) {
            PolyNode* newNode = create_node(temp1->coeff*temp2->coeff, temp1->power+temp2->power);
            anstemp->next = newNode;
            anstemp = newNode;
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    sort(ans);
    deleteDuplicates(ans);
    return ans;
}

int main() {
    PolyNode* p1 = create_node(0, 0);
    insert(p1, 2, 2);
    insert(p1, 3, 1);
    insert(p1, 7, 5);
    insert(p1, 5, 5);
    insert(p1, 3, 1);
    insert(p1, 3, 3);
    insert(p1, 3, 5);
    display(p1);
    // PolyNode* p2 = create_node(0, 0);
    // insert(p2, 6, 2);
    // insert(p2, 3, 7);
    // insert(p2, 2, 5);
    // display(p2);
    // PolyNode* sum = addPoly(p1, p2);
    // display(sum);
    // PolyNode* product = multiplyPoly(p1, p2);
    // display(product);
}