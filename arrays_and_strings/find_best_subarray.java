public int findBestSubarray(int[] nums, int k)
{
    int curr = 0;
    for (int i = 0; i < k; i++)
    {
        curr += nums[i];
    }

    int max_sum = curr;
    for (int i = k; i < nums.length; i++)
    {
        curr += nums[i] - nums[i - k];
        max_sum = Math.max(max_sum, curr);
    }

    return max_sum;
}