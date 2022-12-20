/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @param {number} limit
 * @returns {boolean[]}
 */
var answerQueries = function(nums, queries, limit) {
    let prefix = [nums[0]];
    for (let i = 1; i < nums.length; i++)
    {
        prefix.push(nums[i] + prefix[prefix.length - 1]);
    }

    let ans = [];
    for (const [x, y] of queries)
    {
        let curr = prefix[y] - prefix[x] + nums[x];
        ans.push(curr < limit);
    }

    return ans;
}