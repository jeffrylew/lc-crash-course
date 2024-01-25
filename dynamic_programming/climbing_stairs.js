/**
 * @param {number} n
 * @return {number}
 */
var climbStairsDS1 = function(n) {
    const climb_Stairs = curr_step => {
        if (curr_step > n)
        {
            return 0;
        }

        if (curr_step == n)
        {
            return 1;
        }

        return climb_Stairs(curr_step + 1) + climb_Stairs(curr_step + 2);
    }

    return climb_Stairs(0);
};

/**
 * @param {number} n
 * @return {number}
 */
var climbStairsDS2 = function(n) {
    let memo = new Array(n + 1).fill(0);

    const climb_Stairs = curr_step => {
        if (curr_step > n)
        {
            return 0;
        }

        if (curr_step == n)
        {
            return 1;
        }

        if (memo[curr_step] > 0)
        {
            return memo[curr_step];
        }

        memo[curr_step] =
            climb_Stairs(curr_step + 1) + climb_Stairs(curr_step + 2);
        return memo[curr_step];
    }

    return climb_Stairs(0);
};

/**
 * @param {number} n
 * @return {number}
 */
var climbStairsDS3 = function(n) {
    if (n == 1)
    {
        return 1;
    }

    let dp = new Array(n + 1).fill(0);
    dp[1] = 1;
    dp[2] = 2;

    for (let curr_step = 3; curr_step <= n; curr_step++)
    {
        dp[curr_step] = dp[curr_step - 1] + dp[curr_step - 2];
    }

    return dp[n];
};
