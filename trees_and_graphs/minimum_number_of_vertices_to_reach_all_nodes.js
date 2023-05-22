var findSmallestSetOfVertices = function(n, edges)
{
    let indegree = new Array(n).fill(0);

    for (const [x, y] of edges)
    {
        indegree[y]++;
    }

    let ans = [];
    for (let i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            ans.push(i);
        }
    }

    return ans;
}