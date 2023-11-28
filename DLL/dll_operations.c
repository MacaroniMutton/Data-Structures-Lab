/*
 * File: dll_operations.c
 * Author: Siddhartha Chandra
 * Email: siddhartha_chandra@spit.ac.in
 * Created: September 24, 2023
 * Description: This implements ADT for storing a DLL and performing operations on it. Use dummy nodes - header and trailer, in your implementation
 */

#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node {
    int val;
    struct Node* prev;
    struct Node* next;
} Node;


Node* create_node(int val){
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
}

// pos == 0 indicates start of the DLL
// pos == -1 indicates end of the DLL
// pos == n indicates intermediate node pos
// is_after = true => insert after 'pos'
// is_after = false => insert before 'pos'
void insert_at_pos(Node* header, Node* trailer, int val, int pos, bool is_after) {
    Node* newNode = create_node(val);
    if(header->next==NULL || header->next==trailer) {
        header->next = newNode;
        newNode->prev = header;
        newNode->next = trailer;
        trailer->prev = newNode;
    }
    else if(pos==0) {
        newNode->next = header->next;
        newNode->prev = header;
        header->next->prev = newNode;
        header->next = newNode;
    }
    else if(pos==-1) {
        newNode->next = trailer;
        newNode->prev = trailer->prev;
        trailer->prev->next = newNode;
        trailer->prev = newNode;
    }
    else {
        Node* temp = header->next;
        int count = 0;
        while(count<pos) {
            temp = temp->next;
            count++;
        }
        if(is_after) {
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
        }
        else {
            newNode->next = temp;
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            temp->prev = newNode;
        }
    }
}

// pos == 0 indicates start of the DLL
// pos == -1 indicates end of the DLL
// pos == n indicates intermediate node pos
void delete_at_pos(Node* header, Node* trailer, int pos) {
    if(header->next==NULL || header->next==trailer) {
        printf("Doubly Linked List is empty.\n");
        return;
    }
    Node* del;
    if(pos==0) {
        del = header->next;
        header->next = del->next;
        del->next->prev = header;
    }
    else if(pos==-1) {
        del = trailer->prev;
        del->prev->next = trailer;
        trailer->prev = del->prev;
    }
    else {
        del = header->next;
        int count = 0;
        while(count<pos) {
            del = del->next;
            count++;
        }
        del->prev->next = del->next;
        del->next->prev = del->prev;
    }
    free(del);
}

// pos == 0 indicates start of the DLL
// pos == -1 indicates end of the DLL
// pos == n indicates intermediate node pos

// this swaps the 2 nodes in the DLL at positions pos_1 and pos_2
// please note, the nodes have to be swapped and not just values
void swap(Node* header, Node* trailer, int pos_1, int pos_2) {
    Node* node1 = header->next;
    Node* node2 = header->next;
    int count = 0;
    while(count<pos_1) {
        node1 = node1->next;
        count++;
    }
    count = 0;
    while(count<pos_2) {
        node2 = node2->next;
        count++;
    }
    if(node1->next==node2) {
        node1->prev->next = node2;
        node2->next->prev = node1;
        node1->next = node2->next;
        node2->prev = node1->prev;
        node1->prev = node2;
        node2->next = node1;
    }
    else if(node2->next==node1) {
        node2->prev->next = node1;
        node1->next->prev = node2;
        node2->next = node1->next;
        node1->prev = node2->prev;
        node2->prev = node1;
        node1->next = node2;
    }
    else {
        node1->prev->next = node2;
        node2->prev->next = node1;
        node1->next->prev = node2;
        node2->next->prev = node1;
        Node* temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
        temp = node1->prev;
        node1->prev = node2->prev;
        node2->prev = temp;
    }

}

// void reverse(Node* header, Node* trailer) {
//     if(header==NULL || header->next==trailer) {
//         printf("Doubly Linked List is empty.\n");
//         return;
//     }
//     int n = 0;
//     for(Node* temp = header->next; temp!=trailer; temp = temp->next) {
//         n++;
//     }
//     for(int i = 0; i<n/2; i++) {
//         swap(header, trailer, i, n-1-i);
//     }
// }

void reverse(Node* header, Node* trailer) {
    if(header->next==trailer)
        return;
    header->next->prev = trailer;
    trailer->prev->next = header;
    header->prev = trailer->prev;
    trailer->next = header->next;
    header->next = NULL;
    trailer->prev = NULL;
    Node* temp = trailer;
    while(temp!=NULL) {
        Node* t = temp->next;
        temp->next = temp->prev;
        temp->prev = t;
        temp = temp->prev;
    }
}

int swapVal(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sort(Node* header, Node* trailer) {
    int n = 0;
    Node* temp = header->next;
    while (temp != trailer) {
        n++;
        temp = temp->next;
    }

    for (int i = 0; i < n - 1; i++) {
        Node* tempj = header->next;
        for (int j = 0; j < n - 1 - i; j++) {
            Node* node1 = tempj;
            Node* node2 = tempj->next;

            if (node1->val > node2->val) {
                swapVal(&node1->val, &node2->val);
            }
            tempj = tempj->next;
        }
    }
}


void display(Node *header, Node* trailer){
    for(Node* temp = header->next; temp!=trailer; temp = temp->next) {
        printf("%d", temp->val);
        if(temp!=trailer->prev) {
            printf(" <-> ");
        }
    }
    printf("\n");
}

int main() {
    Node* header = create_node(0);
    Node* trailer = create_node(0);
    insert_at_pos(header, trailer, 4, 0, true);
    display(header, trailer);
    insert_at_pos(header, trailer, 6, 0, true);
    display(header, trailer);
    insert_at_pos(header, trailer, 6, -1, true);
    display(header, trailer);
    insert_at_pos(header, trailer, 8, 2, true);
    display(header, trailer);
    insert_at_pos(header, trailer, 7, 2, false);
    display(header, trailer);
    swap(header, trailer, 1, 2);
    display(header, trailer);
    reverse(header, trailer);
    display(header, trailer);
    sort(header, trailer);
    display(header, trailer);
    delete_at_pos(header, trailer, 2);
    display(header, trailer);
    delete_at_pos(header, trailer, 1);
    display(header, trailer);
    reverse(header, trailer);
    display(header, trailer);
    return 0;
}

