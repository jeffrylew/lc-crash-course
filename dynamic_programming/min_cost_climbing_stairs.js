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

var minCostClimbingStairsBottomUp = function(cost) {
    const n = cost.length;

    // Step 2
    let dp = new Array(n + 1).fill(0);

    // Step 3: Base case(s) are implicitly defined as they are 0

    // Step 4
    for (let i = 2; i <= n; i++)
    {
        // Step 5
        dp[i] = Math.min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }

    // Step 6
    return dp[n];
};
