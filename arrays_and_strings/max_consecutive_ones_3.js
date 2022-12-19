/**
 * @param {number[]} nums
 * @param {number} k
 * @returns {number}
 */
var longestOnes = function(nums, k) {
    let left = 0;
    let right;

    for (right = 0; right < nums.length; right++)
    {
        if (nums[right] == 0)
        {
            k--;
        }

        if (k < 0)
        {
            if (nums[left] == 0)
            {
                k++;
            }
            left++;
        }
    }

    return right - left;
}