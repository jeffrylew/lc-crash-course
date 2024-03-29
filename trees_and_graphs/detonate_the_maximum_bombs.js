/**
 * @param {number[][]} bombs
 * @return {number}
 */
var maximumDetonation = function(bombs)
{
    const dfsRecursive = (curr_node, visited, graph) => {
        visited.add(curr_node);

        let count = 1;

        if (!graph.has(curr_node))
        {
            graph.set(curr_node, []);
        }

        for (const neighbor of graph.get(curr_node))
        {
            if (!visited.has(neighbor))
            {
                count += dfsRecursive(neighbor, visited, graph);
            }
        }

        return count;
    }

    const dfsIterative = (curr_node, graph) => {
        let stack = [curr_node];
        let visited = new Set([curr_node]);

        while (stack.length)
        {
            const node = stack.pop();

            if (!graph.has(node))
            {
                graph.set(node, []);
            }

            for (const neighbor of graph.get(node))
            {
                if (!visited.has(neighbor))
                {
                    visited.add(neighbor);
                    stack.push(neighbor);
                }
            }
        }

        return visited.size;
    }

    const bfs = (curr_node, graph) => {
        let queue = [curr_node];
        let visited = new Set([curr_node]);

        while (queue.length)
        {
            const currNodesInQueue = queue.length;
            let nextQueue = [];

            for (let i = 0; i < currNodesInQueue; i++)
            {
                const node = queue[i];

                if (!graph.has(node))
                {
                    graph.set(node, []);
                }

                for (const neighbor of graph.get(node))
                {
                    if (!visited.has(neighbor))
                    {
                        visited.add(neighbor);
                        nextQueue.push(neighbor);
                    }
                }
            }

            queue = nextQueue;
        }

        return visited.size;
    }

    let graph = new Map();
    const n = bombs.length;

    // Build the graph
    for (let i = 0; i < n; i++)
    {
        for (let j = i + 1; j < n; j++)
        {
            const xi = bombs[i][0];
            const yi = bombs[i][1];
            const ri = bombs[i][2];

            const xj = bombs[j][0];
            const yj = bombs[j][1];
            const rj = bombs[j][2];

            const dx2 = (xi - xj) * (xi - xj);
            const dy2 = (yi - yj) * (yi - yj);
            const ri2 = ri * ri;
            const rj2 = rj * rj;

            if (ri2 >= dx2 + dy2)
            {
                if (!graph.has(i))
                {
                    graph.set(i, []);
                }

                graph.get(i).push(j);
            }

            if (rj2 >= dx2 + dy2)
            {
                if (!graph.has(j))
                {
                    graph.set(j, []);
                }

                graph.get(j).push(i);
            }
        }
    }

    let answer = 0;

    for (let i = 0; i < n; i++)
    {
        /**
         * Recursive DFS
         * 
        let visited = new Set();
        const count = dfsRecursive(i, visited, graph);
        answer = Math.max(answer, count);
         */
        
        /**
         * Iterative DFS
         * 
        answer = Math.max(answer, dfsIterative(i, graph));
         */
        
        answer = Math.max(answer, bfs(i, graph));
    }

    return answer;
};