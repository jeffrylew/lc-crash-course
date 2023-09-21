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