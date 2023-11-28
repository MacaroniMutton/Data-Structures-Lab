// Implement BFS & DFS traversal for graphs.
// You need to make use of an adjacency matrix for representing the graph
// The structure below should allow you to handle both directed and undirected graphs.
// For traversals, the respective function should accept starting node for traversal and perform traversal (BFS/ DFS).

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Vertex;

typedef struct Queue
{
    int front;
    int rear;
    unsigned size;
    Vertex *array;

}Queue;

Queue* initialize_queue(unsigned size){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->size = size;
    queue->front = -1;
    queue->rear = -1;
    
    queue->array = (Vertex *)malloc(queue->size * sizeof(Vertex));
    if (queue->array == NULL) {
        free(queue);
        exit(EXIT_FAILURE);
    }
    return queue;
}

// 1 -> isEmpty
int isEmpty(Queue* queue){
    return (queue->front == -1 && queue->rear == -1);
}

// 3 -> isFull
int isFull(Queue* queue){
    int next_pos = (queue->rear + 1) % queue->size;
    return queue->front == next_pos;
}

// 6 -> front
Vertex front(Queue* queue){
    if (isEmpty(queue)) {
        printf("Error: Queue is empty!\n");
        return -1;
    }
    return queue->array[queue->front];
}

// 7 -> rear
Vertex rear(Queue* queue){
    if (isEmpty(queue)) {
        printf("Error: Queue is empty!\n");
        return -1;
    }
    return queue->array[queue->rear];
}

// 0 -> display
void display_queue(Queue* queue){
    if (isEmpty(queue))
        printf("The queue is empty\n\n");
    else {
        printf("front --> ");
        for (int i=queue->front; i != queue->rear; i = (i + 1) % queue->size)
            printf("%d ", queue->array[i]);

        // additionally display rear element of queue
        printf("%d ", rear(queue));
        printf("<-- rear\n\n");
    }
}



// 4 -> enqueue
void enqueue(Queue *queue, Vertex vertex){
    if (isFull(queue)){
        printf("Error: Queue is already full!\n");
    }
    else{
        // if empty queue, both front and rear get assigned to 0
        // else only rear moves by 1
        if (isEmpty(queue))
            queue->front = queue->rear = 0;
        else
            queue->rear = (queue->rear + 1) % queue->size;
        
        queue->array[queue->rear] = vertex;
    }
    
}

// 5 -> dequeue
Vertex dequeue(Queue* queue){
    if (isEmpty(queue)) {
        printf("Error: Queue is empty!\n");
        return -1;
    }
    else {
        Vertex res;
        res = queue->array[queue->front];
        if (queue->front == queue->rear)    
            queue->front = queue->rear = -1;
        else 
            queue->front = (queue->front + 1) % queue->size;
        
        return res;
    }
}



typedef enum {
    WHITE,
    GRAY,
    BLACK
} Color;

// vertices are denoted by integers 0..N-1

typedef enum {BFS, DFS} TraversalType;
typedef struct Edge {Vertex u; Vertex v;} Edge;

typedef struct AdjListNode {
    Vertex dest;
    struct AdjListNode* next;
} AdjListNode;

typedef struct GraphRep {
    AdjListNode** adjLists; //adjacency list
    int nV; // #vertices
    int nE; // #edges
    bool is_directed; // 'true' if graph is a directed graph

    // ---Additional properties for BFS and DFS--
    TraversalType type;
    // Source vertex for traversal
    Vertex source;
    // Array to store predecessors for vertices
    Vertex *predecessor;   

    // Array to store colors
    Color *color;           

    // Array to store:
    // distance from source for all vertices (For BFS)
    // OR
    // time of arrival from source for all vertices (For DFS)
    int *distance;      

    // NOTE: Only for DFS
    // stores the time at which a given vertex has been fully explored
    int *finish; 

} GraphRep;

AdjListNode* create_node(Vertex data) {
    AdjListNode* node = (AdjListNode*)malloc(sizeof(AdjListNode));
    node->dest = data;
    node->next = NULL;
    return node;
}

GraphRep* init_graph(int num_vertices, bool is_directed) {
    GraphRep* g = (GraphRep*)malloc(sizeof(GraphRep));
    g->adjLists = (AdjListNode**)malloc(num_vertices * sizeof(AdjListNode*));
    for (int i = 0; i < num_vertices; i++) {
        g->adjLists[i] = NULL; // Initialize each list as empty
    }
    g->nV = num_vertices;
    g->nE = 0;
    g->is_directed = is_directed;
    g->predecessor = (Vertex*)malloc(sizeof(Vertex) * num_vertices);
    g->color = (Color*)malloc(sizeof(Color) * num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        g->color[i] = WHITE;
    }
    g->distance = (int*)malloc(sizeof(int) * num_vertices);
    g->finish = (int*)malloc(sizeof(int) * num_vertices);

    return g;
}

void insert_edge(GraphRep* graph, Edge e) {
    // Create a new node for the destination vertex
    AdjListNode* newNode = create_node(e.v);

    // Update the adjacency list of the source vertex
    AdjListNode* current = graph->adjLists[e.u];
    AdjListNode* prev = NULL;

    // Traverse the list to find the correct position for the new node
    while (current != NULL && current->dest < e.v) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        // Insert at the beginning
        newNode->next = graph->adjLists[e.u];
        graph->adjLists[e.u] = newNode;
    } else {
        // Insert in the middle or at the end
        prev->next = newNode;
        newNode->next = current;
    }

    // If the graph is undirected, add the reverse edge as well
    if (!graph->is_directed) {
        AdjListNode* reverseNode = create_node(e.u);

        current = graph->adjLists[e.v];
        prev = NULL;

        // Traverse the list to find the correct position for the new node
        while (current != NULL && current->dest < e.u) {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            // Insert at the beginning
            reverseNode->next = graph->adjLists[e.v];
            graph->adjLists[e.v] = reverseNode;
        } else {
            // Insert in the middle or at the end
            prev->next = reverseNode;
            reverseNode->next = current;
        }
    }

    // Increment the edge count
    graph->nE++;
}

void remove_edge(GraphRep* graph, Edge e) {
    // Remove the edge from the adjacency list of the source vertex
    AdjListNode* current = graph->adjLists[e.u];
    AdjListNode* prev = NULL;

    while (current != NULL && current->dest != e.v) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            graph->adjLists[e.u] = current->next;
        }

        free(current);
    }

    // If the graph is undirected, remove the reverse edge as well
    if (!graph->is_directed) {
        current = graph->adjLists[e.v];
        prev = NULL;

        while (current != NULL && current->dest != e.u) {
            prev = current;
            current = current->next;
        }

        if (current != NULL) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                graph->adjLists[e.v] = current->next;
            }

            free(current);
        }
    }

    // Decrement the edge count
    graph->nE--;
}



// NOTE: During both DFS and BFS traversals, when at a vertex that is connected with multiple vertices, always pick the connecting vertex which has the lowest value first
// Both traversals will always update the following attributes of the Graph:
// 1. source -> stores the value of the starting vertex for the traversal
// 2. type -> stores the traversal type (BFS or DFS)
// 3. color --> indicates if all vertices have been visited or not. Post traversal, all vertices should be BLACK
// 4. predecessor --> this array would hold the predecessor for a given vertex (indicated by the array index). 

// NOTE: BFS Traversal should additionally update the following in the graph:
// 1. distance --> this array would hold the number of hops it takes to reach a given vertex (indicated by the array index) from the source. 
void traverse_bfs(GraphRep* graph, Vertex source) {
    graph->source = source;
    graph->type = BFS;

    // Initialize color, predecessor, and distance arrays
    for (int i = 0; i < graph->nV; i++) {
        graph->color[i] = WHITE;
        graph->predecessor[i] = -1;
        graph->distance[i] = 0;
    }

    graph->color[source] = GRAY;
    graph->distance[source] = 0;
    graph->predecessor[source] = -1;

    Queue* queue = initialize_queue(graph->nV);
    enqueue(queue, source);

    while (!isEmpty(queue)) {
        Vertex u = dequeue(queue);
        printf("%d ", u);

        // Traverse the adjacency list of the current vertex
        AdjListNode* current = graph->adjLists[u];
        while (current != NULL) {
            Vertex v = current->dest;
            if (graph->color[v] == WHITE) {
                graph->color[v] = GRAY;
                graph->distance[v] = graph->distance[u] + 1;
                graph->predecessor[v] = u;
                enqueue(queue, v);
            }
            current = current->next;
        }

        graph->color[u] = BLACK;
    }

    printf("\n");
}


void dfs_visit(GraphRep* graph, Vertex u) {
    static int time = 0;
    printf("%d ", u);
    time = time + 1;
    graph->distance[u] = (time);
    graph->color[u] = GRAY;

    // Traverse the adjacency list of the current vertex
    AdjListNode* current = graph->adjLists[u];
    while (current != NULL) {
        Vertex v = current->dest;
        if (graph->color[v] == WHITE) {
            graph->predecessor[v] = u;
            dfs_visit(graph, v);
        }
        current = current->next;
    }

    time = time + 1;
    graph->finish[u] = time;
    graph->color[u] = BLACK;
}

// NOTE: DFS Traversal should additionally update the following in the graph:
// 1. distance --> Assuming 1 hop to equal 1 time unit, this array would hold the time of discovery a given vertex (indicated by the array index) from the source. 
// 2. finish --> Assuming 1 hop to equal 1 time unit, this array would hold the time at which exploration concludes for a given vertex (indicated by the array index). 
void traverse_dfs(GraphRep* graph, Vertex source) {
    graph->source = source;
    graph->type = DFS;

    // Initialize color, predecessor, and distance arrays
    for (int i = 0; i < graph->nV; i++) {
        graph->color[i] = WHITE;
        graph->predecessor[i] = -1;
        graph->distance[i] = 0;
    }

    // Traverse the DFS starting from the source
    dfs_visit(graph, source);

    printf("\n");
}




// displays the path from the current 'source' in graph to the provided 'destination'. 
// The graph holds the value of the traversal type, so the function should let the caller know what kind of traversal was done on the graph and from which vertex, along with the path.
void display_path(GraphRep *graph, Vertex destination) {
    if(graph->source==destination) {
        if(graph->type==BFS) {
            printf("BFS traversal was performed on the graph\n");
        }
        else if(graph->type==DFS) {
            printf("DFS traversal was performed on the graph\n");
        }
        printf("%d ", graph->source);
    }
    else if(graph->predecessor[destination]==-1) {
        printf("No path from %d to %d exists.", graph->source, destination);
    }
    else {
        display_path(graph, graph->predecessor[destination]);
        printf("%d ", destination);
    }
}

// display the graph in the matrix form
void display_graph(GraphRep* graph) {
    printf("Vertex | Adjacent Vertices\n");
    printf("-------|-------------------\n");

    for (int i = 0; i < graph->nV; i++) {
        printf("%6d | ", i);

        // Traverse the adjacency list for the current vertex
        AdjListNode* current = graph->adjLists[i];
        while (current != NULL) {
            printf("%d ", current->dest);
            current = current->next;
        }

        printf("\n");
    }

    printf("\n");
}

int main() {
    int num_vertices = 10;
    bool is_directed = false;
    GraphRep* graph = init_graph(num_vertices, is_directed);
    Edge e;
    e.u=0;
    e.v=9;
    insert_edge(graph, e);
    e.u=9;
    e.v=5;
    insert_edge(graph, e);
    e.u=5;
    e.v=8;
    insert_edge(graph, e);
    e.u=5;
    e.v=6;
    insert_edge(graph, e);
    e.u=6;
    e.v=4;
    insert_edge(graph, e);
    e.u=4;
    e.v=2;
    insert_edge(graph, e);
    e.u=2;
    e.v=8;
    insert_edge(graph, e);
    e.u=6;
    e.v=1;
    insert_edge(graph, e);
    e.u=1;
    e.v=3;
    insert_edge(graph, e);
    e.u=3;
    e.v=8;
    insert_edge(graph, e);
    e.u=3;
    e.v=7;
    insert_edge(graph, e);
    e.u=7;
    e.v=8;
    insert_edge(graph, e);
    e.u=1;
    e.v=0;
    insert_edge(graph, e);
    e.u=7;
    e.v=5;
    insert_edge(graph, e);
    e.u=9;
    e.v=4;
    insert_edge(graph, e);
    e.u=0;
    e.v=2;
    insert_edge(graph, e);
    display_graph(graph);

    printf("Source: 8\nBFS Traversal : ");
    traverse_bfs(graph, 8);

    printf("\nSource : 8      Destination : 4\n");
    display_path(graph, 4);
    printf("\n\n");

    printf("Source: 8\nDFS Traversal : ");
    traverse_dfs(graph, 8);

    printf("\nSource : 8      Destination : 4\n");
    display_path(graph, 4);
    printf("\n\n");


    return 0;
}
