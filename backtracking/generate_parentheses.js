/**
 * @param {number} n
 * @return {string[]}
 */
var generateParenthesisDS1 = function(n) {
    let answer = [];
    let queue = [""];

    const isValid = pstring => {
        let leftCount = 0;

        for (const p of pstring)
        {
            if (p == '(')
            {
                leftCount++;
            }
            else
            {
                leftCount--;
            }

            if (leftCount < 0)
            {
                return false;
            }
        }

        return leftCount == 0;
    };

    while (queue.length)
    {
        const currQueueLength = queue.length;
        let nextQueue = [];

        for (let j = 0; j < currQueueLength; j++)
        {
            const curString = queue[j];

            // If the length of curString is 2 * n,
            // add it to answer if it is valid
            if (curString.length == 2 * n)
            {
                if (isValid(curString))
                {
                    answer.push(curString);
                }
                continue;
            }

            nextQueue.push(curString + ")");
            nextQueue.push(curString + "(");
        }

        queue = nextQueue;
    }

    return answer;
};
