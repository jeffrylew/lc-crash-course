class Solution
{
    // 2D array for memoization defined with maximum nums size (1001)
    // and maximum split/subarray count k = min(50, nums.length)
    Integer[][] memo = new Integer[1001][51];

    private int getMinimumLargestSplitSum(
        int[] prefixSum, int currIdx, int subarrCount)
    {
        int nums_len = prefixSum.length - 1;

        // Already calculated the answer so no need to recurse
        if (memo[currIdx][subarrCount] != null)
        {
            return memo[currIdx][subarrCount];
        }

        // Base Case: If there is only one subarray left then all remaining
        // numbers must go into current subarray. Return sum of remaining nums
        if (subarrCount == 1)
        {
            memo[currIdx][subarrCount] =
                prefixSum[nums_len] - prefixSum[currIdx];
            return memo[currIdx][subarrCount];
        }

        // Otherwise, use recurrence relation to determine min largest subarray
        // sum between currIdx and end of nums with subarrCount subarrays left
        int minimumLargestSplitSum = Integer.MAX_VALUE;
        for (int i = currIdx; i <= nums_len - subarrCount; i++)
        {
            // Store the sum of the first subarray
            int firstSplitSum = prefixSum[i + 1] - prefixSum[currIdx];

            // Find the maximum subarray sum for the current first split
            int largestSplitSum =
                Math.max(firstSplitSum,
                         getMinimumLargestSplitSum(prefixSum,
                                                   i + 1,
                                                   subarrCount - 1));

            // Find the minimum among all possible combinations
            minimumLargestSplitSum =
                Math.min(minimumLargestSplitSum, largestSplitSum);

            if (firstSplitSum >= minimumLargestSplitSum)
            {
                break;
            }
        }

        return memo[currIdx][subarrCount] = minimumLargestSplitSum;
    }

    public int splitArrayDS1(int[] nums, int k)
    {
        // Store the prefix sum of nums
        int nums_len = nums.length;
        int[] prefixSum = new int[nums_len + 1];

        for (int i = 0; i < nums_len; i++)
        {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        return getMinimumLargestSplitSum(prefixSum, 0, k);
    }
}
