/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[]} restricted
 * @return {number}
 */
var reachableNodesBFS = function(n, edges, restricted)
{
    let neighbors = new Map();
    for (let node = 0; node < n; node++)
    {
        neighbors.set(node, []);
    }

    for (const [nodeA, nodeB] of edges)
    {
        neighbors.get(nodeA).push(nodeB);
        neighbors.get(nodeB).push(nodeA);
    }

    let seen = new Array(n).fill(false);
    for (const node of restricted)
    {
        seen[node] = true;
    }

    let ans = 0;
    let queue = [0];
    seen[0] = true;

    while (queue.length)
    {
        const currNode = queue.shift();
        ans++;

        for (const nextNode of neighbors.get(currNode))
        {
            if (!seen[nextNode])
            {
                seen[nextNode] = true;
                queue.push(nextNode);
            }
        }
    }

    return ans;
};

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[]} restricted
 * @return {number}
 */
var reachableNodesDFSRecursive = function(n, edges, restricted)
{
    let neighbors = new Map();
    for (let node = 0; node < n; node++)
    {
        neighbors.set(node, []);
    }

    for (const [nodeA, nodeB] of edges)
    {
        neighbors.get(nodeA).push(nodeB);
        neighbors.get(nodeB).push(nodeA);
    }

    let seen = new Array(n).fill(false);
    for (const node of restricted)
    {
        seen[node] = true;
    }

    let ans = 0;

    const dfsRecursive = (start) => {
        ans++;
        seen[start] = true;
        
        for (const nextNode of neighbors.get(start))
        {
            if (!seen[nextNode])
            {
                dfsRecursive(nextNode);
            }
        }
    }

    dfsRecursive(0);
    return ans;
};