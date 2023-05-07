from collections import defaultdict

def build_graph(edges):
    graph = defaultdict(list)

    for x, y in edges:
        graph[x].append(y)

        # Uncomment following line if graph is undirected
        # graph[y].append(x)
    
    return graph