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
