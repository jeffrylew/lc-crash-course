public double findMaxAverage(int[] nums, int k)
{
    int curr_sum = 0;
    for (int i = 0; i < k; i++)
    {
        curr_sum += nums[i];
    }

    int max_sum = curr_sum;
    for (int i = k; i < nums.length; i++)
    {
        curr_sum += nums[i] - nums[i - k];
        max_sum = Math.max(max_sum, curr_sum);
    }

    return max_sum * 1.0 / k;
}