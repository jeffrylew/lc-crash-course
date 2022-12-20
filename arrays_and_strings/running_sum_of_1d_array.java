public int[] runningSum1(int[] nums)
{
    int[] prefix = new int[nums.length];
    prefix[0] = nums[0];

    for (int i = 1; i < nums.length; i++)
    {
        prefix[i] = nums[i] + prefix[i - 1];
    }

    return prefix;
}

public int[] runningSum2(int[] nums)
{
    for (int i = 1; i < nums.length; i++)
    {
        nums[i] += nums[i - 1];
    }
    return nums;
}