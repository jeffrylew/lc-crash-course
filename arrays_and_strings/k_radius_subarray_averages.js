/**
 * @param {number[]} nums
 * @param {number} k
 * @returns {number[]}
 */
var getAveragesDS1 = function(nums, k)
{
    // When a single element is considered then its average is the num itself
    if (k === 0)
    {
        return nums;
    }

    const windowSize = 2 * k + 1;
    const nums_len = nums.length;
    const averages = new Array(nums_len).fill(-1);

    // Case when any index does not have k elements on either side
    if (windowSize > nums_len)
    {
        return averages;
    }

    // Generate prefix array for nums
    // prefix[idx + 1] is the sum of all elements from index 0 to idx
    const prefix = new Array(nums_len + 1).fill(0);
    for (let idx = 0; idx < nums_len; idx++)
    {
        prefix[idx + 1] = prefix[idx] + nums[idx];
    }

    // Only iterate on indices that have at least k elements on either side
    // i.e. Indices from k (inclusive) to nums_len - k (exclusive)
    for (let idx = k; idx < (nums_len - k); idx++)
    {
        const leftBound = idx - k;
        const rightBound = idx + k;

        const subArraySum = prefix[rightBound + 1] - prefix[leftBound];
        averages[idx] = Math.floor(subArraySum / windowSize);
    }

    return averages;
};

/**
 * @param {number[]} nums
 * @param {number} k
 * @returns {number[]}
 */
var getAveragesDS2 = function(nums, k)
{
    // When a single element is considered then its average is the num itself
    if (k === 0)
    {
        return nums;
    }

    const windowSize = 2 * k + 1;
    const nums_len = nums.length;
    const averages = new Array(nums_len).fill(-1);

    // Case when all indices do not have k elements on either side
    if (windowSize > nums_len)
    {
        return averages;
    }

    // Get sum of first window in nums vector
    let windowSum = 0;
    for (let idx = 0; idx < windowSize; ++idx)
    {
        windowSum += nums[idx];
    }
    averages[k] = Math.floor(windowSum / windowSize);

    // Iterate on rest of indices that have at least k elements on either side
    for (let idx = windowSize; idx < nums_len; ++idx)
    {
        // Remove discarded element and add new element for current window sum
        // idx is index of newly inserted element
        // (idx - windowSize) is index of last removed element
        windowSum = windowSum - nums[idx - windowSize] + nums[idx];
        averages[idx - k] = Math.floor(windowSum / windowSize);
    }

    return averages;
};
