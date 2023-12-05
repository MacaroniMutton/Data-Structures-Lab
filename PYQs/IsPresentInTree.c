#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {NOTPRESENT, ROOT, LEFTCHILD, RIGHTCHILD} Status;
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

void isKeyPresent(TreeNode* root, int key, Status start, Status* result) {
    if(root==NULL) {
        return;
    }
    if(root->data==key) {
        *result = start;
    }
    isKeyPresent(root->left, key, LEFTCHILD, result);
    isKeyPresent(root->right, key, RIGHTCHILD, result);
}

int main() {
    TreeNode* root = create_node(1);
    TreeNode* node1 = create_node(2);
    TreeNode* node2 = create_node(3);
    TreeNode* node3 = create_node(4);
    TreeNode* node4 = create_node(5);
    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node1->right = node4;
    Status start = ROOT;
    Status result = NOTPRESENT;
    printf("Enter key : ");
    int key;
    scanf("%d", &key);
    isKeyPresent(root, key, start, &result);
    if(result==NOTPRESENT)
        printf("Not Present\n");
    else if(result==LEFTCHILD)
        printf("Left Child\n");
    else if(result==RIGHTCHILD)
        printf("Right Child\n");
    else
        printf("Root");
    return 0;
}

    //         1
    //       /   \
    //      2     3
    //    /   \
    //   4     5

