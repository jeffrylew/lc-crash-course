/**
 * @param {number[]} temperatures
 * @returns {number[]}
 */
var dailyTemperatures = function(temperatures)
{
    let stack = [];
    let answer = new Array(temperatures.length).fill(0);

    for (let i = 0; i < temperatures.length; i++)
    {
        while (stack.length
               && temperatures[stack[stack.length - 1]] < temperatures[i])
        {
            const j = stack.pop();
            answer[j] = i - j;
        }

        stack.push(i);
    }

    return answer;
};