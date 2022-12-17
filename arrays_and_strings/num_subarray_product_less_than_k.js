
/**
 * @param {number[]} nums
 * @param {number} k
 * @returns {number}
 */
var numSubarrayProductLessThanK = function(nums, k) {
    if (k <= 1)
    {
        return 0;
    }

    let curr_product = 1;
    let num_subarrays = 0;
    let left = 0;

    for (let right = 0; right < nums.length; right++)
    {
        curr_product *= nums[right];

        while (curr_product >= k)
        {
            curr_product /= nums[left++];
        }

        num_subarrays += right - left + 1;
    }

    return num_subarrays;
}