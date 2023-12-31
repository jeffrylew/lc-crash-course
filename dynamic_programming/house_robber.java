class SolutionTopDown
{
    Map<Integer, Integer> memo = new HashMap<>();

    public int dp(int i, int[] nums)
    {
        // Base cases
        if (i == 0)
        {
            return nums[0];
        }

        if (i == 1)
        {
            return Math.max(nums[0], nums[1]);
        }

        if (memo.containsKey(i))
        {
            return memo.get(i);
        }

        // Recurrence relation
        memo.put(i, Math.max(dp(i - 1, nums), dp(i - 2, nums) + nums[i]));
        return memo.get(i);
    }

    public int rob(int[] nums)
    {
        if (nums.length == 1)
        {
            // Prevent out of bounds error
            return nums[0];
        }

        return dp(nums.length - 1, nums);
    }
}

public int robBottomUp(int[] nums)
{
    if (nums.length == 1)
    {
        // Avoid out-of-bounds error from setting base case
        return nums[0];
    }

    int nums_length = nums.length;
    int[] dp = new int[nums_length];

    // Base cases
    dp[0] = nums[0];
    dp[1] = Math.max(nums[0], nums[1]);

    for (int i = 2; i < nums_length; i++)
    {
        // Recurrence relation
        dp[i] = Math.max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    return dp[nums_length - 1];
}

public int robBottomUpOptimized(int[] nums)
{
    if (nums.length == 1)
    {
        // Avoid out-of-bounds error from setting base case
        return nums[0];
    }

    int nums_length = nums.length;

    // Base cases
    int backTwo = nums[0];
    int backOne = Math.max(nums[0], nums[1]);

    for (int i = 2; i < nums_length; i++)
    {
        // backTwo becomes backOne, and backOne is updated
        int temp = backOne;
        backOne = Math.max(backOne, backTwo + nums[i]);
        backTwo = temp;
    }

    return backOne;
}
