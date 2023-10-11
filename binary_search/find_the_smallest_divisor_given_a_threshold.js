/**
 * @param {number[]} nums
 * @param {number} threshold
 * @returns {number}
 */
const smallestDivisorDS1 = function(nums, threshold) {
    const maxElement = nums.reduce((a, b) => Math.max(a, b), nums[0]);

    // Iterate on all divisors
    for (let divisor = 1; divisor <= maxElement; ++divisor)
    {
        let sumOfDivisionResults = 0;
        let thresholdExceeded = false;

        // Divide all numbers of array and sum the result
        for (const num of nums)
        {
            sumOfDivisionResults += Math.ceil((1.0 * num) / divisor);

            if (sumOfDivisionResults > threshold)
            {
                thresholdExceeded = true;
                break;
            }
        }

        // If threshold was not exceeded then return current divisor
        if (!thresholdExceeded)
        {
            return divisor;
        }
    }

    return -1;
};