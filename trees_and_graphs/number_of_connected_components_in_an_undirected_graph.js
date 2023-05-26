/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var countComponents = function(n, edges) {
    const dfsRecursive = (graph, seen, start) => {
        seen[start] = true;

        for (const neighbor of graph.get(start))
        {
            if (!seen[neighbor])
            {
                dfsRecursive(graph, seen, neighbor);
            }
        }
    }

    let components = 0;

    let visited = new Array(n).fill(false);
    let graph = new Map();

    for (let i = 0; i < n; i++)
    {
        graph.set(i, []);
    }

    for (const [x, y] of edges)
    {
        graph.get(x).push(y);
        graph.get(y).push(x);
    }

    for (let node = 0; node < n; node++)
    {
        if (!visited[node])
        {
            components++;
            dfsRecursive(graph, visited, node);
        }
    }

    return components;
};