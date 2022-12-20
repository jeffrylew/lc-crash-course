public int waysToSplitArray1(int[] nums)
{
    long[] prefix = new long[nums.length];
    prefix[0] = nums[0];

    for (int i = 1; i < nums.length; i++)
    {
        prefix[i] = nums[i] + prefix[i - 1];
    }

    int ans = 0;
    for (int i = 0; i < nums.length - 1; i++)
    {
        long leftSection = prefix[i];
        long rightSection = prefix[nums.length - 1] - prefix[i];
        if (leftSection >= rightSection)
        {
            ans++;
        }
    }

    return ans;
}

public int waysToSplitArray2(int[] nums)
{
    int  ans = 0;
    long leftSection = 0;
    long total = 0;

    for (int num : nums)
    {
        total += num;
    }

    for (int i = 0; i < nums.length - 1; i++)
    {
        leftSection += nums[i];
        const long rightSection = total - leftSection;
        if (leftSection >= rightSection)
        {
            ans++;
        }
    }

    return ans;
}