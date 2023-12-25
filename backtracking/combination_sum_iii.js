/**
 * @param {number} k
 * @param {number} n
 * @return {number[][]}
 */
var combinationSum3DS1 = function(k, n) {
    let results = [];
    let comb = [];

    const backtrack = (remain, next_start) => {
        if (remain == 0 && comb.length == k)
        {
            // Note: It's important to make a deep copy here otherwise the
            // combination would be reverted in another branch of backtracking
            results.push([...comb]);
            return;
        }
        else if (remain < 0 || comb.length == k)
        {
            // Exceeded the scope, no need to explore further
            return;
        }

        // Iterate through the reduced list of candidates
        for (let i = next_start; i < 9; i++)
        {
            comb.push(i + 1);
            backtrack(remain - i - 1, i + 1);
            comb.pop();
        }
    };

    backtrack(n, 0);
    return results;
};
