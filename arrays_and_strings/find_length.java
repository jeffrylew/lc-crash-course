public int findLength(int[] nums, int k)
{
    int left = 0;
    int curr = 0;
    int max_subarray_size = 0;

    for (int right = 0; right < nums.length; right++)
    {
        curr += nums[right];
        while (curr > k)
        {
            curr -= nums[left++];
        }

        max_subarray_size = Math.max(max_subarray_size, right - left + 1);
    }

    return max_subarray_size;
}