#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* link;
} Node;

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->link = NULL;
    return node;
}

Node* shuffleMerge(Node* n1, Node* n2) {
    Node* temp1 = n1->link;
    Node* temp2 = n2->link;
    Node* ans = create_node(0);
    Node* anstemp = ans;
    while(temp1!=NULL || temp2!=NULL) {
        if(temp1==NULL) {
            anstemp->link = temp2;
            break;
        }
        if(temp2==NULL) {
            anstemp->link = temp1;
            break;
        }
        Node* newNode1 = create_node(temp1->data);
        Node* newNode2 = create_node(temp2->data);
        anstemp->link = newNode1;
        anstemp = newNode1;
        anstemp->link = newNode2;
        anstemp = newNode2;
        temp1 = temp1->link;
        temp2 = temp2->link;
    }
    return ans;
}

void display(Node* head) {
    if(head==NULL || head->link==NULL)
        return;
    Node* temp = head->link;
    while(temp->link!=NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("%d\n", temp->data);
}

int main() {
    Node* n1 = create_node(0);
    Node* anode1 = create_node(1);
    Node* anode2 = create_node(2);
    Node* anode3 = create_node(3);
    Node* anode4 = create_node(4);
    Node* anode5 = create_node(5);
    n1->link = anode1;
    anode1->link = anode2;
    anode2->link = anode3;
    anode3->link = anode4;
    anode4->link = anode5;
    anode5->link = NULL;

    Node* n2 = create_node(0);
    Node* bnode1 = create_node(7);
    Node* bnode2 = create_node(13);
    Node* bnode3 = create_node(11);
    n2->link = bnode1;
    bnode1->link = bnode2;
    bnode2->link = bnode3;
    bnode3->link = NULL;

    display(n1);
    display(n2);

    Node* n3 = shuffleMerge(n1, n2);
    display(n3);

    return 0;
}