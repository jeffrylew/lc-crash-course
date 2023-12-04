/**
 * @param {number[][]} graph
 * @return {number[][]}
 */
var allPathsSourceTargetDS1 = function(graph) {
    const backtrack = (currNode) => {
        if (currNode == target)
        {
            results.push([...path]);
            return;
        }

        for (const nextNode of graph[currNode])
        {
            path.push(nextNode);
            backtrack(nextNode);
            path.pop();
        }
    }
    const target = graph.length - 1;
    let path = [0];
    let results = [];
    backtrack(0);
    return results;
};

/**
 * @param {number[][]} graph
 * @return {number[][]}
 */
var allPathsSourceTargetDS2 = function(graph) {
    const allPathsToTarget = (currNode) => {
        if (memo.has(currNode))
        {
            return memo.get(currNode);
        }

        let results = [];
        if (currNode == target)
        {
            results.push([target]);
        }
        else
        {
            for (const nextNode of graph[currNode])
            {
                for (const path of allPathsToTarget(nextNode))
                {
                    results.push([currNode, ...path]);
                }
            }
        }

        memo.set(currNode, results);
        return results;
    }

    const target = graph.length - 1;
    let memo = new Map();
    return allPathsToTarget(0);
};
