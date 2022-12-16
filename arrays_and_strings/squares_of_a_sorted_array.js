/**
 * @param {number[]} nums
 * @return {number[]}
 */
var sortedSquaresDS1 = function(nums) {
    const N   = nums.length;
    let   ans = [];

    for (let i = 0; i < N; i++)
    {
        ans.push(nums[i] * nums[i]);
    }

    ans.sort((a, b) => { return a - b });
    return ans;
};

let sortedSquaresDS2 = (nums) => {
    const N   = nums.length;
    const ans = [];

    let left  = 0;
    let right = N - 1;

    for (let i = N - 1; i >= 0; i--)
    {
        let square = 0;
        if (Math.abs(nums[left]) < Math.abs(nums[right]))
        {
            square = nums[right--];
        }
        else
        {
            square = nums[left++];
        }
        ans[i] = square * square;
    }

    return ans;
};