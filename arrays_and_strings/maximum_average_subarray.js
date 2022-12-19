/**
 * @param {number[]} nums
 * @param {number} k
 * @returns {number}
 */
var findMaxAverage = function(nums, k) {
    let curr_sum = 0;
    for (let i = 0; i < k; i++)
    {
        curr_sum += nums[i];
    }

    let max_sum = curr_sum;
    for (let i = k; i < nums.length; i++)
    {
        curr_sum += nums[i] - nums[i - k];
        max_sum = Math.max(max_sum, curr_sum);
    }

    return max_sum * 1.0 / k;
}