/**
 * @param {number[]} nums
 * @returns {number}
 */
var waysToSplitArray1 = function(nums) {
    let prefix = [nums[0]];

    for (let i = 1; i < nums.length; i++)
    {
        prefix.push(nums[i] + prefix[prefix.length - 1]);
    }

    let ans = 0;
    for (let i = 0; i < nums.length - 1; i++)
    {
        let leftSection = prefix[i];
        let rightSection = prefix[prefix.length - 1] - prefix[i];
        if (leftSection >= rightSection)
        {
            ans++;
        }
    }

    return ans;
}