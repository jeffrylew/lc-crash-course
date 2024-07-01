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

/**
 * @param {number[]} nums
 * @return {number}
 */
var findMaxLengthDS2 = function(nums)
{
    const nums_len = nums.length;

    let arr_of_counts = new Array(2 * nums_len + 1).fill(-2);
    arr_of_counts[nums_len] = -1;

    let max_len = 0;
    let count = 0;

    for (let idx = 0; idx < nums_len; idx++)
    {
        count = count + (nums[idx] == 0 ? -1 : 1);

        const idx_in_2n_plus_1 = count + nums_len;
        if (arr_of_counts[idx_in_2n_plus_1] >= -1)
        {
            max_len = Math.max(max_len, idx - arr_of_counts[idx_in_2n_plus_1]);
        }
        else
        {
            arr_of_counts[idx_in_2n_plus_1] = idx;
        }
    }

    return max_len;
};

/**
 * @param {number[]} nums
 * @return {number}
 */
var findMaxLengthDS3 = function(nums)
{
    let count_idx = new Map();
    count_idx.set(0, -1);

    let max_len = 0;
    let count = 0;

    for (let idx = 0; idx < nums.length; idx++)
    {
        count += (nums[idx] == 0 ? -1 : 1);

        if (count_idx.has(count))
        {
            max_len = Math.max(max_len, idx - count_idx.get(count));
        }
        else
        {
            count_idx.set(count, idx);
        }
    }

    return max_len;
};
