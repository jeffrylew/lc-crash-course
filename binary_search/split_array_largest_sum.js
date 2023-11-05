/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var splitArrayDS1 = function(nums, k)
{
    const memo = new Array(1001).fill(-1).map(() => new Array(51).fill(-1));

    const nums_len = nums.length;
    const prefixSum = new Array(nums.length + 1).fill(0);

    for (let i = 0; i < nums.length; i++)
    {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    const getMinimumLargestSplitSum = (prefixSum, currIdx, subarrCount) => {
        // Already calculated the answer so no need to recurse
        if (memo[currIdx][subarrCount] != -1)
        {
            return memo[currIdx][subarrCount];
        }

        // Base case: If there is only one subarray left then all remaining
        // numbers must go into current subarray. Return sum of remaining nums.
        if (subarrCount == 1)
        {
            memo[currIdx][subarrCount] =
                prefixSum[nums_len] - prefixSum[currIdx];
            return memo[currIdx][subarrCount];
        }

        // Otherwise, use recurrence relation to determine the min largest
        // subarray sum between currIdx and end of nums with subarrCount left
        let minimumLargestSplitSum = Number.MAX_SAFE_INTEGER;
        for (let i = currIdx; i <= nums_len - subarrCount; i++)
        {
            // Store the sum of the first subarray
            const firstSplitSum = prefixSum[i + 1] - prefixSum[currIdx];

            // Find maximum subarray sum for the current first split
            const largestSplitSum =
                Math.max(getMinimumLargestSplitSum(
                    prefixSum, i + 1, subarrCount - 1), firstSplitSum);

            // Find minimum among all possible combinations
            minimumLargestSplitSum =
                Math.min(minimumLargestSplitSum, largestSplitSum);

            if (firstSplitSum >= minimumLargestSplitSum)
            {
                break;
            }
        }

        return memo[currIdx][subarrCount] = minimumLargestSplitSum;
    };

    return getMinimumLargestSplitSum(prefixSum, 0, k);
};