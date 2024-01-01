/**
 * @param {number[]} nums
 * @returns {number}
 */
var robTopDown = function(nums) {
    const dp = i => {
        // Base cases
        if (i == 0)
        {
            return nums[0];
        }

        if (i == 1)
        {
            return Math.max(nums[0], nums[1]);
        }

        if (memo[i] != -1)
        {
            return memo[i];
        }

        // Recurrence relation
        memo[i] = Math.max(dp(i - 1), dp(i - 2) + nums[i]);
        return memo[i];
    }

    if (nums.length == 1)
    {
        // Prevent out of bounds error
        return nums[0];
    }

    let memo = new Array(nums.length).fill(-1);
    return dp(nums.length - 1);
};

/**
 * @param {number[]} nums
 * @returns {number}
 */
var robBottomUp = function(nums) {
    const nums_length = nums.length;

    if (nums_length == 1)
    {
        // Prevent out-of-bounds error
        return nums[0];
    }

    let dp = new Array(nums_length).fill(0);

    // Base cases
    dp[0] = nums[0];
    dp[1] = Math.max(nums[0], nums[1]);

    for (let i = 2; i < nums_length; i++)
    {
        dp[i] = Math.max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    return dp[nums_length - 1];
};
