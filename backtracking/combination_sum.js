/**
 * @param {number[]} candidates
 * @param {number} target
 * @returns {number[][]}
 */
var combinationSum = function(candidates, target) {
    const backtrack = (path, start, curr) => {
        if (curr == target)
        {
            ans.push([...path]);
            return;
        }

        for (let i = start; i < candidates.length; i++)
        {
            const num = candidates[i];
            if (curr + num <= target)
            {
                path.push(num);
                backtrack(path, i, curr + num);
                path.pop();
            }
        }
    }

    let ans = [];
    backtrack([], 0, 0);
    return ans;
};
