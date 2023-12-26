/**
 * @param {number[]} cost
 * @returns {number}
 */
var minCostClimbingStairsTopDown = function(cost) {
    const dp = i => {
        if (i <= 1)
        {
            // 3. Base case(s)
            return 0;
        }

        if (memo.has(i))
        {
            return memo.get(i);
        }

        // 2. Recurrence relation
        memo.set(i, Math.min(dp(i - 1) + cost[i - 1], dp(i - 2) + cost[i - 2]));
        return memo.get(i);
    }

    let memo = new Map();
    return dp(cost.length);
};
