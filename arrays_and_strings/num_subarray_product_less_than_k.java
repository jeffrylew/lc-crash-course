public int numSubarrayProductLessThanK(int[] nums, int k)
{
    if (k <= 1)
    {
        return 0;
    }

    int num_subarrays = 0;
    int curr_product = 1;
    int left = 0;

    for (int right = 0; right < nums.length; right++)
    {
        curr_product *= nums[right];
        while (curr_product >= k)
        {
            curr_product /= nums[left++];
        }
        num_subarrays += right - left + 1;
    }

    return num_subarrays;
}