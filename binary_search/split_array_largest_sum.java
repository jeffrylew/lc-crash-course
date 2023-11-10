class Solution
{
    // 2D array for memoization defined with maximum nums size (1001)
    // and maximum split/subarray count k = min(50, nums.length)
    Integer[][] memo = new Integer[1001][51];

    int[][] memoDS2 = new int[1001][51];

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

    public int splitArrayDS2(int[] nums, int k)
    {
        // Store the prefix sum of nums
        int nums_len = nums.length;
        int[] prefixSum = new int[nums_len + 1];

        for (int i = 0; i < nums_len; i++)
        {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        for (int subarrCount = 1; subarrCount <= k; subarrCount++)
        {
            for (int currIdx = 0; currIdx < nums_len; currIdx++)
            {
                // Base Case: If there is only one subarray left then all of the
                // remaining numbers must go in the current subarray. Return the
                // sum of the remaining numbers
                if (subarrCount == 1)
                {
                    memoDS2[currIdx][subarrCount] =
                        prefixSum[nums_len] - prefixSum[currIdx];
                    continue;
                }

                // Otherwise, use the recurrence relation to determine the min
                // largest subarray sum between currIdx and the end of the array
                // with subarrCount subarray remaining
                int minimumLargestSplitSum = Integer.MAX_VALUE;
                for (int i = currIdx; i <= nums_len - subarrCount; i++)
                {
                    // Store the sum of the first subarray
                    int firstSplitSum = prefixSum[i + 1] - prefixSum[currIdx];

                    // Find the max subarray sum for the current first split
                    int largestSplitSum =
                        Math.max(firstSplitSum, memoDS2[i + 1][subarrCount - 1]);
                    
                    // Find the minimum among all possible combinations
                    minimumLargestSplitSum =
                        Math.min(minimumLargestSplitSum, largestSplitSum);
                    
                    if (firstSplitSum >= minimumLargestSplitSum)
                    {
                        break;
                    }
                }

                memoDS2[currIdx][subarrCount] = minimumLargestSplitSum;
            }
        }

        return memoDS2[0][k];
    }

    private int minimumSubarraysRequired(int[] nums, int maxSumAllowed)
    {
        int currentSum = 0;
        int splitsRequired = 0;

        for (int element : nums)
        {
            // Add element only if the sum doesn't exceed maxSumAllowed
            if (currentSum + element <= maxSumAllowed)
            {
                currentSum += element;
            }
            else
            {
                // If the element addition makes sum more than maxSumAllowed
                // then increment the splits required and reset sum
                currentSum = element;
                splitsRequired++;
            }
        }

        // Return the number of subarrays, which is the number of splits + 1
        return splitsRequired + 1;
    }

    public int splitArrayDS3(int[] nums, int k)
    {
        // Find the sum of all elements and the maximum element
        int sum = 0;
        int maxElement = Integer.MIN_VALUE;
        for (int element : nums)
        {
            sum += element;
            maxElement = Math.max(maxElement, element);
        }

        // Define the left and right boundaries of binary search
        int left = maxElement;
        int right = sum;
        int minimumLargestSplitSum = 0;

        while (left <= right)
        {
            // Find the mid value
            int maxSumAllowed = left + (right - left) / 2;

            // Find the minimum splits. If splitsRequired is less than
            // or equal to k then move towards smaller values (left)
            if (minimumSubarraysRequired(nums, maxSumAllowed) <= k)
            {
                right = maxSumAllowed - 1;
                minimumLargestSplitSum = maxSumAllowed;
            }
            else
            {
                // Move towards right if splitsRequired is more than k
                left = maxSumAllowed + 1;
            }
        }

        return minimumLargestSplitSum;
    }
}
