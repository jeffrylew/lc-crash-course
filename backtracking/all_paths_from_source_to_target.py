def allPathsSourceTargetDS1(graph: list[list[int]]) -> list[list[int]]:
    target = len(graph) - 1
    results = []

    def backtrack(curr_node, path):
        # If we reach the target, no need to explore further
        if curr_node == target:
            results.append(path[:])
            return

        for next_node in graph[curr_node]:
            path.append(next_node)
            backtrack(next_node, path)
            path.pop()

    path = [0]
    backtrack(0, path)
    return results
