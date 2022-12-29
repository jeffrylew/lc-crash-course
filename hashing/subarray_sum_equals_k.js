/**
 * @param {number[]} nums
 * @param {number} k
 * @returns {number}
 */
var subarraySum = function(nums, k) {
    let counts = new Map();
    counts.set(0, 1);

    let ans = 0;
    let curr = 0;

    for (const num of nums)
    {
        curr += num;
        ans += counts.get(curr - k) || 0;
        counts.set(curr, (counts.get(curr) || 0) + 1);
    }

    return ans;
}