/**
 * @param {number[]} nums
 * @return {number}
 */
const largestUniqueNumber = (nums) => {
    let counts = new Map();
    for (const num of nums)
    {
        counts.set(num, (counts.get(num) || 0) + 1);
    }

    let result = -1;
    for (const num of Array.from(counts.keys()))
    {
        if (counts.get(num) == 1)
        {
            result = Math.max(result, num);
        }
    }

    return result;
}