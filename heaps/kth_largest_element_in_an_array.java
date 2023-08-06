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

public int quickSelect(List<Integer> nums, int k)
{
    int pivotIndex = new Random().nextInt(nums.size());
    int pivot = nums.get(pivotIndex);

    List<Integer> left = new ArrayList<>();
    List<Integer> mid = new ArrayList<>();
    List<Integer> right = new ArrayList<>();

    for (int num : nums)
    {
        if (num > pivot)
        {
            left.add(num);
        }
        else if (num < pivot)
        {
            right.add(num);
        }
        else
        {
            mid.add(num);
        }
    }

    if (k <= left.size())
    {
        return quickSelect(left, k);
    }

    if (left.size() + mid.size() < k)
    {
        return quickSelect(right, k - left.size() - mid.size());
    }

    return pivot;
}

public int findKthLargestDS3(int[] nums, int k)
{
    List<Integer> list = new ArrayList<>();
    for (int num : nums)
    {
        list.add(num);
    }

    return quickSelect(list, k);
}