/**
 * @param {number[]} nums
 * @return {number}
 */
var findMaxLengthDS1 = function(nums)
{
    let max_len = 0;

    for (let start = 0; start < nums.length; start++)
    {
        let zeros = 0;
        let ones = 0;

        for (let end = start; end < nums.length; end++)
        {
            if (nums[end] == 0)
            {
                zeros++;
            }
            else
            {
                ones++;
            }

            if (zeros == ones)
            {
                max_len = Math.max(max_len, end - start + 1);
            }
        }
    }

    return max_len;
};
