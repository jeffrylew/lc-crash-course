/**
 * @param {number[]} nums
 * @returns {number}
 */
var maximumSum1 = function(nums) {
    let getDigitSum = num => {
        let digitSum = 0;
        while (num > 0)
        {
            digitSum += num % 10;
            num = Math.floor(num / 10);
        }

        return digitSum;
    }

    let dic = new Map();
    for (const num of nums)
    {
        const digitSum = getDigitSum(num);
        if (!dic.has(digitSum))
        {
            dic.set(digitSum, []);
        }
        dic.get(digitSum).push(num);
    }

    let ans = -1;
    for (const [key, curr] of dic)
    {
        if (curr.length > 1)
        {
            curr.sort((a, b) => b - a);
            ans = Math.max(ans, curr[0] + curr[1]);
        }
    }

    return ans;
}
