class SolutionTopDown
{
    Map<Integer, Integer> memo = new HashMap<>();

    public int dp(int i, int[] nums)
    {
        if (memo.containsKey(i))
        {
            return memo.get(i);
        }

        // Base case
        int ans = 1;

        // Recurrence relation
        for (int j = 0; j < i; j++)
        {
            if (nums[i] > nums[j])
            {
                ans = Math.max(ans, dp(j, nums) + 1);
            }
        }

        memo.put(i, ans);
        return ans;
    }

    public int lengthOfLIS(int[] nums)
    {
        int ans = 0;
        for (int i = 0; i < nums.length; i++)
        {
            ans = Math.max(ans, dp(i, nums));
        }

        return ans;
    }
}

public int lengthOfLISBottomUp(int[] nums)
{
    int nums_length = nums.length;
    int[] dp = new int[n];
    Arrays.fill(dp, 1);

    int ans = 1;
    for (int i = 0; i < nums_length; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            dp[i] = Math.max(dp[i], dp[j] + 1);
            ans = Math.max(ans, dp[i]);
        }
    }

    return ans;
}
