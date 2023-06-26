/**
 * @param {string[][]} equations
 * @param {number[]} values
 * @param {string[][]} queries
 * @return {number[]}
 */
var calcEquation = function(equations, values, queries)
{
    const answerQuery = (start, end) => {
        // No info on this node
        if (!graph.has(start))
        {
            return -1;
        }

        let seen = new Set([start]);
        let stack = [[start, 1]];

        while (stack.length)
        {
            const [node, ratio] = stack.pop();

            if (node == end)
            {
                return ratio;
            }

            if (graph.has(node))
            {
                for (const [neighbor, val] of graph.get(node))
                {
                    if (!seen.has(neighbor))
                    {
                        seen.add(neighbor);
                        stack.push([neighbor, ratio * val]);
                    }
                }
            }
        }

        return -1;
    }

    let graph = new Map();

    for (let i = 0; i < equations.length; i++)
    {
        const [numerator, denominator] = equations[i];
        const val = values[i];

        if (!graph.has(numerator))
        {
            graph.set(numerator, new Map());
        }

        if (!graph.has(denominator))
        {
            graph.set(denominator, new Map());
        }

        graph.get(numerator).set(denominator, val);
        graph.get(denominator).set(numerator, 1 / val);
    }

    let ans = [];

    for (const [numerator, denominator] of queries)
    {
        ans.push(answerQuery(numerator, denominator));
    }

    return ans;
};