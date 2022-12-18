/**
 * @param {number[]} nums
 * @param {number} k
 * @returns {number}
 */
var findBestSubarray = function(nums, k) {
    let curr = 0;
    for (let i = 0; i < k; i++)
    {
        curr += nums[i];
    }

    let max_sum = curr;
    for (let i = k; i < nums.length; i++)
    {
        curr += nums[i] - nums[i - k];
        max_sum = Math.max(max_sum, curr);
    }

    return max_sum;
}