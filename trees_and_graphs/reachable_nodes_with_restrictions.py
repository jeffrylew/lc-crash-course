from collections import defaultdict
from collections import deque

def reachableNodesBFS(
    n: int,
    edges: list[list[int]],
    restricted: list[int]
) -> int:
    # Store all edges in neighbors
    neighbors = defaultdict(list)
    for node_a, node_b in edges:
        neighbors[node_a].append(node_b)
        neighbors[node_b].append(node_a)
    
    # Mark the nodes in restricted as visited
    seen = [False] * n
    for node in restricted:
        seen[node] = True
    
    # Store all nodes to be visited in queue
    ans = 0
    queue = deque([0])
    seen[0] = True

    while queue:
        curr_node = queue.popleft()
        ans += 1

        for next_node in neighbors[curr_node]:
            if not seen[next_node]:
                seen[next_node] = True
                queue.append(next_node)
    
    return ans

def reachableNodeDFSRecursive(
    n: int,
    edges: list[list[int]],
    restricted: list[int]
) -> int:
    neighbors = defaultdict(list)
    for node_a, node_b in edges:
        neighbors[node_a].append(node_b)
        neighbors[node_b].append(node_a)
    
    seen = [False] * n
    for node in restricted:
        seen[node] = True

    def dfsRecursive(curr_node):
        nonlocal ans
        ans += 1

        seen[curr_node] = True

        for next_node in neighbors[curr_node]:
            if not seen[next_node]:
                dfsRecursive(next_node)
    
    ans = 0
    dfsRecursive(0)
    return ans

def reachableNodeDFSIterative(
    n: int,
    edges: list[list[int]],
    restricted: list[int]
) -> int:
    neighbors = defaultdict(set)
    for node_a, node_b in edges:
        neighbors[node_a].add(node_b)
        neighbors[node_b].add(node_a)
    
    seen = [False] * n
    for node in restricted:
        seen[node] = True
    
    stack = [0]
    ans = 0
    seen[0] = True

    while stack:
        curr_node = stack.pop()
        ans += 1

        for next_node in neighbors[curr_node]:
            if not seen[next_node]:
                seen[next_node] = True
                stack.append(next_node)
    
    return ans

class UnionFind:
    def __init__(self, n):
        self.root = list(range(n))
        self.rank = [1] * n
    
    def find(self, x):
        if self.root[x] != x:
            self.root[x] = self.find(self.root[x])
        return self.root[x]
    
    def union(self, x, y):
        root_x, root_y = self.find(x), self.find(y)
        if root_x != root_y:
            if self.rank[root_x] > self.rank[root_y]:
                root_x, root_y = root_y, root_x
            
            self.rank[root_y] += self.rank[root_x]
            self.root[root_x] = root_y
    
    def getSize(self, x):
        return self.rank[self.find(x)]

def reachableNodesDSU(
    n: int,
    edges: list[list[int]],
    restricted: list[int]
) -> int:
    rest_set_ = set(restricted)
    uf = UnionFind(n)

    for node_a, node_b in edges:
        if node_a not in rest_set_ and node_b not in rest_set_:
            uf.union(node_a, node_b)
    
    return uf.getSize(0)
