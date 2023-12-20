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

/**
 * @param {number} n
 * @return {string[]}
 */
var generateParenthesisDS2 = function(n) {
    let answer = [];
    let curString = "";

    const backtrack = (leftCount, rightCount) => {
        if (curString.length == 2 * n)
        {
            answer.push(curString);
            return;
        }

        if (leftCount < n)
        {
            curString += "(";
            backtrack(leftCount + 1, rightCount);
            curString = curString.substring(0, curString.length - 1);
        }

        if (rightCount < leftCount)
        {
            curString += ")";
            backtrack(leftCount, rightCount + 1);
            curString = curString.substring(0, curString.length - 1);
        }
    };

    backtrack(0, 0);
    return answer;
};

/**
 * @param {number} n
 * @return {string[]}
 */
var generateParenthesisDS3 = function(n) {
    if (n == 0)
    {
        return [""];
    }

    let answer = [];
    for (let leftCount = 0; leftCount < n; ++leftCount)
    {
        for (const leftString of generateParenthesisDS3(leftCount))
        {
            for (const rightString of generateParenthesisDS3(n - 1 - leftCount))
            {
                answer.push("(" + leftString + ")" + rightString);
            }
        }
    }

    return answer;
};
