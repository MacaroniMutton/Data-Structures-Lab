typedef struct Queue {
    ExprTreeNode** arr;
    int size;
    int front;
    int rear;
}Queue;

Queue* create_queue(int size) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->size = size;
    q->arr = (ExprTreeNode**)malloc(size*sizeof(ExprTreeNode*));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isQueueEmpty(Queue* queue) {
    if(queue->front==-1)
        return true;
    else
        return false;
}

bool isQueueFull(Queue* queue) {
    if((queue->rear+1)%queue->size==queue->front)
        return true;
    else
        return false;
}

void enqueue(Queue* queue, ExprTreeNode* node) {
    if(isQueueFull(queue))
        printf("Queue is full!");
    else {
        if(queue->front==-1) {
            queue->front++;
            queue->front %= queue->size;
        }
        queue->rear++;
        queue->rear %= queue->size;
        queue->arr[queue->rear] = node;
    }
}

ExprTreeNode* dequeue(Queue* queue) {
    if(isQueueEmpty(queue))
        return NULL;
    else {
        ExprTreeNode* popped = queue->arr[queue->front];
        if(queue->front==queue->rear) {
            queue->front = queue->rear = -1;
        }
        else {
            queue->front++;
            queue->front %= queue->size;
        }
        return popped;
    }
}

ExprTreeNode* front(Queue* queue) {
    if(queue->front==-1)
        return NULL;
    return queue->arr[queue->front];
}

ExprTreeNode* rear(Queue* queue) {
    if(queue->rear==-1)
        return NULL;
    return queue->arr[queue->rear];
}

void levelOrderTraversal(ExprTreeNode* root) {
    if(root==NULL)
        return;
    Queue* queue = create_queue(10);
    enqueue(queue, root);
    enqueue(queue, NULL);
    while(!isQueueEmpty(queue)) {
        ExprTreeNode* temp = front(queue);
        dequeue(queue);
        if(temp!=NULL) {
            if(temp->type == OPERAND)
                printf("%.0f ", temp->data.operand);
            else
                printf("%c ", temp->data.operation);
            if(temp->left!=NULL)
                enqueue(queue, temp->left);
            if(temp->right!=NULL)
                enqueue(queue, temp->right);
        }
        else {
            printf("\n");
            if(!isQueueEmpty(queue)) {
                enqueue(queue, NULL);
            }
        }
    }
}


void preOrderTraversal(ExprTreeNode* root) {
    if(root==NULL)
        return;

    if(root->type == OPERAND)
        printf("%.2f ", root->data.operand);
    else
        printf("%c ", root->data.operation);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void inOrderTraversal(ExprTreeNode* root) {
    if(root==NULL)
        return;

    inOrderTraversal(root->left);
    if(root->type == OPERAND)
        printf("%.2f ", root->data.operand);
    else
        printf("%c ", root->data.operation);
    inOrderTraversal(root->right);
}

void postOrderTraversal(ExprTreeNode* root) {
    if(root==NULL)
        return;

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    if(root->type == OPERAND)
        printf("%.2f ", root->data.operand);
    else
        printf("%c ", root->data.operation);
}

