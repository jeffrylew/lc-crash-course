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

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[]} restricted
 * @return {number}
 */
var reachableNodesDFSIterative = function(n, edges, restricted)
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
    seen[0] = true;
    let stack = [0];

    while (stack.length)
    {
        const currNode = stack.pop();

        ans++;

        for (const nextNode of neighbors.get(currNode))
        {
            if (!seen[nextNode])
            {
                seen[nextNode] = true;
                stack.push(nextNode);
            }
        }
    }

    return ans;
};

class UnionFind
{
    constructor(n)
    {
        this.rank = new Array(n).fill(1);
        this.root = new Array(n);

        for (let node = 0; node < n; node++)
        {
            this.root[node] = node;
        }
    }

    find(x)
    {
        if (this.root[x] != x)
        {
            this.root[x] = this.find(this.root[x]);
        }
        return this.root[x];
    }

    union(x, y)
    {
        let rootX = this.find(x);
        let rootY = this.find(y);

        if (rootX != rootY)
        {
            if (this.rank[rootX] > this.rank[rootY])
            {
                const tmp = rootX;
                rootX = rootY;
                rootY = tmp;
            }

            this.root[rootX] = rootY;
            this.rank[rootY] += this.rank[rootX];
        }
    }

    getSize(x)
    {
        return this.rank[this.find(x)];
    }
};

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[]} restricted
 * @return {number}
 */
var reachableNodesDSU = function(n, edges, restricted)
{
    const uf = new UnionFind(n);
    let restSet = new Set();

    for (const node of restricted)
    {
        restSet.add(node);
    }

    for (const [nodeA, nodeB] of edges)
    {
        if (!restSet.has(nodeA) && !restSet.has(nodeB))
        {
            uf.union(nodeA, nodeB);
        }
    }

    return uf.getSize(0);
};