public int partitionArray(int[] nums, int k)
{
    Arrays.sort(nums);
    
    int ans = 1;
    int x = nums[0];

    for (int i = 1; i < nums.length; i++)
    {
        if (nums[i] - x > k)
        {
            x = nums[i];
            ans++;
        }
    }

    return ans;
}