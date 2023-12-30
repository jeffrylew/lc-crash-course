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
