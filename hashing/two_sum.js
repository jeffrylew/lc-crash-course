/**
 * @param {number[]} nums
 * @param {number[]} target
 * @returns {number[]}
 */
var twoSum = function(nums, target) {
    let dic = new Map();
    for (let i = 0; i < nums.length; i++)
    {
        const num = nums[i];
        const complement = target - num;
        if (dic.has(complement))
        {
            return [i, dic.get(complement)];
        }

        dic.set(num, i);
    }

    return [-1, -1];
}