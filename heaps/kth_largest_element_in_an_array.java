public int findKthLargestDS1(int[] nums, int k)
{
    Arrays.sort(nums);

    // Can't sort int[] in descending order in Java
    // Sort ascending and then return the kth element from the end
    return nums[nums.length - k];
}

public int findKthLargestDS2(int[] nums, int k)
{
    PriorityQueue<Integer> minHeap = new PriorityQueue<>();
    for (int num : nums)
    {
        minHeap.add(num);

        if (minHeap.size() > k)
        {
            minHeap.remove();
        }
    }

    return minHeap.peek();
}