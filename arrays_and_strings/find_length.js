/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var findLength = function(nums, k) {
    let left = 0, curr = 0, max_subarray_size = 0;

    for (let right = 0; right < nums.length; right++)
    {
        curr += nums[right];

        while (curr > k)
        {
            curr -= nums[left++];
        }

        max_subarray_size = Math.max(max_subarray_size, right - left + 1);
    }

    return max_subarray_size;
}