public int[] maxSlidingWindow(int[] nums, int k)
{
    int[] ans = new int[nums.length - k + 1];
    ArrayDeque<Integer> deque = new ArrayDeque<>();

    for (int i = 0; i < nums.length; i++)
    {
        // Maintain monotonically decreasing deque
        // All elements smaller than the current one have no
        // chance of being the maximum so get rid of them
        while (!deque.isEmpty() && nums[i] > nums[deque.getLast()])
        {
            deque.removeLast();
        }

        deque.addLast(i);

        // deque[0] is the index of the max element
        // if deque[0] + k == i then it is outside the window
        if (deque.getFirst() + k == i)
        {
            deque.removeFirst();
        }

        // Only add to the answer array once our window has reached size k
        if (i >= k - 1)
        {
            ans[i - k + 1] = nums[deque.getFirst()];
        }
    }

    return ans;
}