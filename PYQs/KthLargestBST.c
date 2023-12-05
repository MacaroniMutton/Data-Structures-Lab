#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* create_node(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* constructBST(TreeNode* root, int data) {
    if(root==NULL)
        return create_node(data);

    if(data>root->data) 
        root->right = constructBST(root->right, data);
    if(data<root->data)
        root->left = constructBST(root->left, data);

    return root;
}

TreeNode* inorderPredecessor(TreeNode* node) {
    if(node==NULL || node->left==NULL)
        return NULL;
    TreeNode* temp = node->left;
    while(temp!=NULL) {
        temp = temp->right;
    }
    return temp;
}

TreeNode* inorderSuccessor(TreeNode* node) {
    if(node==NULL || node->right==NULL)
        return NULL;
    TreeNode* temp = node->right;
    while(temp!=NULL) {
        temp = temp->left;
    }
    return temp;
}

void kLargest(TreeNode* root, int* k, TreeNode** node) {
    if(root==NULL || (*k)==0)
        return;
    
    kLargest(root->right, k, node);
    (*k)--;
    if((*k)==0) {
        *node = root;
        return;
    }
        
    kLargest(root->left, k, node);
}

int main() {
    int choice;
    TreeNode* root = NULL;
    do {
        printf("Enter a node in the Binary Search Tree : ");
        int data;
        scanf("%d", &data);
        root = constructBST(root, data);
        printf("Press 1 to insert another node, or press 0 to exit : ");
        scanf("%d", &choice);
    }while(choice!=0);
    printf("Enter k : ");
    int k;
    scanf("%d", &k);
    TreeNode* node = NULL;
    kLargest(root, &k, &node);
    printf("Kth Largest Node in BST is : %d", node->data);
    return 0;
}