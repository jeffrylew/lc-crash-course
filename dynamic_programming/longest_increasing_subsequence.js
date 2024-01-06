/**
 * @param {number[]} nums
 * @returns {number}
 */
var lengthOfLISTopDown = function(nums) {
    const dp = i => {
        if (memo[i] != -1)
        {
            return memo[i];
        }

        // Base case
        let ans = 1;
        for (let j = 0; j < i; j++)
        {
            if (nums[i] > nums[j])
            {
                ans = Math.max(ans, dp(j) + 1);
            }
        }

        memo[i] = ans;
        return memo[i];
    }

    let memo = new Array(nums.length).fill(-1);
    let ans = 0;
    for (let i = 0; i < nums.length; i++)
    {
        ans = Math.max(ans, dp(i));
    }

    return ans;
};

/**
 * @param {number[]} nums
 * @returns {number}
 */
var lengthOfLISBottomUp = function(nums)
{
    let dp = new Array(nums.length).fill(1);

    for (let i = 0; i < nums.length; i++)
    {
        for (let j = 0; j < i; j++)
        {
            if (nums[i] > nums[j])
            {
                dp[i] = Math.max(dp[i], dp[j] + 1);
            }
        }
    }

    return Math.max(...dp);
};
