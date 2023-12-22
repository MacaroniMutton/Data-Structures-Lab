adjacency_matrix = [
    [0,4,0,0,0,0,0,8,0],
    [4,0,8,0,0,0,0,11,0],
    [0,8,0,7,0,4,0,0,2],
    [0,0,7,0,9,14,0,0,0],
    [0,0,0,9,0,10,0,0,0],
    [0,0,4,14,10,0,2,0,0],
    [0,0,0,0,0,2,0,1,6],
    [8,11,0,0,0,0,1,0,7],
    [0,0,2,0,0,0,6,7,0]
]

print("The graph is : [")
for row in adjacency_matrix:
    print(row)
print("]\n")

spanning_tree = [[0 for i in range(9)] for j in range(9)]
weight_edges = {}
set_list = []

for i in range(len(adjacency_matrix)):
    set_list.append({i})
    for j in range(len(adjacency_matrix[i])):
        if adjacency_matrix[i][j]==0:
            continue
        if not (adjacency_matrix[i][j] in weight_edges):
            weight_edges[adjacency_matrix[i][j]] = []
        weight_edges[adjacency_matrix[i][j]].append((i,j))

weight_edges = dict(sorted(weight_edges.items()))

print("The edges sorted in terms of their weights : ")
for item in weight_edges.items():
    print(item)
print("")

print(set_list)
print("")

for weight,edges in weight_edges.items():
    for edge in edges:
        set_1 = None
        set_2 = None
        for set in set_list:
            if edge[0] in set:
                set_1 = set
            if edge[1] in set:
                set_2 = set
        if set_1 != set_2:
            set_list.append(set_1.union(set_2))
            set_list.remove(set_1)
            set_list.remove(set_2)
            print(f"Insert the edge {edge}  ", end="")
            print(set_list)
            spanning_tree[edge[0]][edge[1]] = weight
            spanning_tree[edge[1]][edge[0]] = weight

print("\nThe minimum cost spanning tree is : [")
for row in spanning_tree:
    print(row)
print("]")

        