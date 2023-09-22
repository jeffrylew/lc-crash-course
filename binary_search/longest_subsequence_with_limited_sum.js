/**
 * @param {number[]} nums
 * @param {number[]} queries
 * @return {number[]}
 */
var answerQueriesDS1 = function(nums, queries)
{
    // Sort nums
    nums.sort((a, b) => a - b);

    const n = nums.length;
    const m = queries.length;

    // For each query, collect numbers from lowest to highest
    // If their sum exceeds the limit query, move on to the next query
    let answer = [];

    for (let query of queries)
    {
        let count = 0;

        for (const num of nums)
        {
            if (query >= num)
            {
                query -= num;
                count++;
            }
            else
            {
                break;
            }
        }

        answer.push(count);
    }

    return answer;
};

/**
 * @param {number[]} nums
 * @param {number[]} queries
 * @return {number[]}
 */
var answerQueriesDS2 = function(nums, queries)
{
    const binarySearch = (nums, target) => {
        let left = 0;
        let right = nums.length;

        while (left < right)
        {
            const mid = Math.floor((left + right) / 2);

            if (nums[mid] > target)
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }

        return left;
    }

    // Get the prefix sum array of the sorted nums
    nums.sort((a, b) => a - b);

    for (let i = 1; i < nums.length; i++)
    {
        nums[i] += nums[i - 1];
    }

    // For each query, find its insertion index in the prefix sum array
    const n = queries.length;
    let answer = [];

    for (const query of queries)
    {
        answer.push(binarySearch(nums, query));
    }

    return answer;
};