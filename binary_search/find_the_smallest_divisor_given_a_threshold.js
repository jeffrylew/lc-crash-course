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

/**
 * @param {number[]} nums
 * @param {number} threshold
 * @returns {number}
 */
const smallestDivisorDS2 = function(nums, threshold) {
    const findDivisionSum = (divisor) => {
        let result = 0;

        for (const num of nums)
        {
            result += Math.ceil((1.0 * num) / divisor);
        }

        return result;
    }

    let ans = -1;
    let low = 1;
    let high = nums.reduce((a, b) => Math.max(a, b), nums[0]);

    // Iterate using binary search on all divisors
    while (low <= high)
    {
        const mid = Math.floor((low + high) / 2);
        const result = findDivisionSum(nums, mid);

        // If current divisor does not exceed threshold then it can be answer
        // but also try smaller divisors, change search space to left half
        if (result <= threshold)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            // Otherwise need a bigger divisor to reduct the result sum
            // so change search space to right half
            low = mid + 1;
        }
    }

    return ans;
};