/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number} source
 * @param {number} destination
 * @return {boolean}
 */
var validPath = function(n, edges, source, destination)
{
    let graph = new Map();
    for (let i = 0; i < n; i++)
    {
        graph.set(i, []);
    }

    for (const [a, b] of edges)
    {
        graph.get(a).push(b);
        graph.get(b).push(a);
    }

    let seen = new Array(n).fill(false);

    const dfsRecursive = currNode => {
        if (currNode == destination)
        {
            return true;
        }

        if (!seen[currNode])
        {
            seen[currNode] = true;
            for (const nextNode of graph.get(currNode))
            {
                if (dfsRecursive(nextNode))
                {
                    return true;
                }
            }
        }

        return false;
    }

    return dfsRecursive(source);
};