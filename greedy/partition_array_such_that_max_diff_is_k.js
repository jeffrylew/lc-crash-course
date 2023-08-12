/**
 * @param {number[]} nums
 * @param {number} k
 * @returns {number}
 */
var partitionArray = function(nums, k)
{
    nums.sort((a, b) => a - b);

    let ans = 1;
    let x = nums[0];

    for (let i = 1; i < nums.length; i++)
    {
        if (nums[i] - x > k)
        {
            x = nums[i];
            ans++;
        }
    }

    return ans;
}