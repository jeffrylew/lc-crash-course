public int findKthLargestDS1(int[] nums, int k)
{
    Arrays.sort(nums);

    // Can't sort int[] in descending order in Java
    // Sort ascending and then return the kth element from the end
    return nums[nums.length - k];
}