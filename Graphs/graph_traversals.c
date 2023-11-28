// Implement BFS & DFS traversal for graphs.
// You need to make use of an adjacency matrix for representing the graph
// The structure below should allow you to handle both directed and undirected graphs.
// For traversals, the respective function should accept starting node for traversal and perform traversal (BFS/ DFS).

#include "queue.c"

GraphRep *init_graph(int num_vertices, bool is_directed) {
    GraphRep* g = (GraphRep*)malloc(sizeof(GraphRep));
    g->edges = (bool**)malloc(num_vertices*sizeof(bool*));
    for(int i = 0; i<num_vertices; i++) {
        g->edges[i] = (bool*)malloc(num_vertices*sizeof(bool));
    }
    for(int i = 0; i<num_vertices; i++) {
        for(int j = 0; j<num_vertices; j++) {
            g->edges[i][j] = 0;
        }
    }
    g->nV = num_vertices;
    g->nE = 0;
    g->is_directed = is_directed;
    g->predecessor = (Vertex*)malloc(sizeof(Vertex)*num_vertices);
    g->color = (Color*)malloc(sizeof(Color)*num_vertices);
    for(int i = 0; i<num_vertices; i++) {
        g->color[i] = WHITE;
    }
    g->distance = (int*)malloc(sizeof(int)*num_vertices);
    g->finish = (int*)malloc(sizeof(int)*num_vertices);
}

void insert_edge(GraphRep *graph, Edge e) {
    if(graph->is_directed) {
       graph->edges[e.u][e.v] = 1; 
    }
    else {
        graph->edges[e.u][e.v] = 1;
        graph->edges[e.v][e.u] = 1;
    }
    graph->nE++;
}

void remove_edge(GraphRep *graph, Edge e) {
    if(graph->is_directed) {
       graph->edges[e.u][e.v] = 0; 
    }
    else {
        graph->edges[e.u][e.v] = 0;
        graph->edges[e.v][e.u] = 0;
    }
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
void traverse_bfs(GraphRep *graph, Vertex source) {
    graph->source = source;
    graph->type = BFS;
    for(int i = 0; i<graph->nV; i++) {
        graph->color[i] = WHITE;
        graph->predecessor[i] = -1;
        graph->distance[i] = 0;
    }
    graph->color[source] = GRAY;
    graph->distance[source] = 0;
    graph->predecessor[source] = -1;
    Queue* queue = initialize_queue(graph->nV);
    enqueue(queue, source);
    while(!isEmpty(queue)) {
        Vertex u = dequeue(queue);
        printf("%d ", u);
        for(Vertex v = 0; v<graph->nV; v++) {
            if(graph->edges[u][v]==1 && graph->color[v]==WHITE) {
                graph->color[v] = GRAY;
                graph->distance[v] = graph->distance[u] + 1;
                graph->predecessor[v] = u;
                enqueue(queue, v);
            }
        }
        graph->color[u] = BLACK;
    }
    printf("\n");
}


void dfs_visit(GraphRep *graph, Vertex u) {
    static int time = 0;
    printf("%d ", u);
    time = time+1;
    graph->distance[u] = time;
    graph->color[u] = GRAY;
    for(Vertex v = 0; v<graph->nV; v++) {
        if(graph->edges[u][v]==1 && graph->color[v]==WHITE) {
            graph->predecessor[v] = u;
            dfs_visit(graph, v);
        }
    }
    time = time+1;
    graph->finish[u] = time;
    graph->color[u] = BLACK;
}

// NOTE: DFS Traversal should additionally update the following in the graph:
// 1. distance --> Assuming 1 hop to equal 1 time unit, this array would hold the time of discovery a given vertex (indicated by the array index) from the source. 
// 2. finish --> Assuming 1 hop to equal 1 time unit, this array would hold the time at which exploration concludes for a given vertex (indicated by the array index). 
void traverse_dfs(GraphRep *graph, Vertex source) {
    graph->source = source;
    graph->type = DFS;
    for(int i = 0; i<graph->nV; i++) {
        graph->color[i] = WHITE;
        graph->predecessor[i] = -1;
        graph->distance[i] = 0;
    }
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
void display_graph(GraphRep *graph) {
    printf("    ");
    for(int i = 0; i<graph->nV; i++) {
        printf("%d  ", i);
    }
    printf("\n");
    printf("   ");
    for(int i = 0; i<graph->nV; i++) {
        printf("---", i);
    }
    printf("\n");
    for(int i = 0; i<graph->nV; i++) {
        printf("%d | ", i);
        for(int j = 0; j<graph->nV; j++) {
            printf("%d  ", graph->edges[i][j]);
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
