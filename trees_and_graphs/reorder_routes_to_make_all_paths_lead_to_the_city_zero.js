/**
 * @param {number} n
 * @param {number[][]} connections
 * @returns {number}
 */
var minReorder = function(n, connections) {
    const convertToHash = (row, col) => {
        return row + "," + col;
    }

    const dfsRecursive = node => {
        let ans = 0;
        for (const neighbor of graph.get(node))
        {
            if (!seen[neighbor])
            {
                if (roads.has(convertToHash(node, neighbor)))
                {
                    ans++;
                }

                seen[neighbor] = true;
                ans += dfsRecursive(neighbor);
            }
        }

        return ans;
    }

    const dfsIterative = start => {
        let ans = 0;

        let stack = [start];
        while (stack.length)
        {
            const node = stack.pop();
            
            for (const neighbor of graph.get(node))
            {
                if (!seen[neighbor])
                {
                    if (roads.has(convertToHash(node, neighbor)))
                    {
                        ans++;
                    }

                    seen[neighbor] = true;
                    stack.push(neighbor);
                }
            }
        }

        return ans;
    }

    let roads = new Set();
    let graph = new Map();
    let seen = new Array(n).fill(false);

    for (let i = 0; i < n; i++)
    {
        graph.set(i, []);
    }

    for (const [x, y] of connections)
    {
        graph.get(x).push(y);
        graph.get(y).push(x);
        roads.add(convertToHash(x, y));
    }

    seen[0] = true;
    return dfsRecursive(0);
    // return dfsIterative(0);
};