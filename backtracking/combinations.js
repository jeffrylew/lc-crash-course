/**
 * @param {number} n
 * @param {number} k
 * @returns {number[][]}
 */
var combine = function(n, k) {
    const backtrack = (curr, i) => {
        if (curr.length == k)
        {
            ans.push([...curr]);
            return;
        }

        for (let num = i; num <= n; num++)
        {
            curr.push(num);
            backtrack(curr, num + 1);
            curr.pop();
        }
    }

    let ans  = [];
    backtrack([], 1);
    return ans;
}