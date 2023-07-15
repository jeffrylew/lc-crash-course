/**
 * @param {string} beginWord
 * @param {string} endWord
 * @param {string[]} wordList
 * @return {number}
 */
var ladderLengthBFS = function(beginWord, endWord, wordList)
{
    const L = beginWord.length;
    
    let allComboMap = new Map();

    for (const word of wordList)
    {
        for (let i = 0; i < L; i++)
        {
            const newWord = word.substring(0, i) + "*" + word.substring(i + 1);

            if (allComboMap.has(newWord))
            {
                allComboMap.get(newWord).push(word);
            }
            else
            {
                allComboMap.set(newWord, [word]);
            }
        }
    }

    let queue = [[beginWord, 1]];
    let visited = new Set([beginWord]);

    while (queue.length)
    {
        const currQueueLength = queue.length;
        let nextQueue = [];

        for (let j = 0; j < currQueueLength; j++)
        {
            const [word, level] = queue[j];

            for (let i = 0; i < L; i++)
            {
                const newWord =
                    word.substring(0, i) + "*" + word.substring(i + 1);
                
                if (!allComboMap.has(newWord))
                {
                    continue;
                }

                for (const adjacentWord of allComboMap.get(newWord))
                {
                    if (adjacentWord == endWord)
                    {
                        return level + 1;
                    }

                    if (!visited.has(adjacentWord))
                    {
                        visited.add(adjacentWord);
                        nextQueue.push([adjacentWord, level + 1]);
                    }
                }
            }
        }

        queue = nextQueue;
    }

    return 0;
};

/**
 * @param {string} beginWord
 * @param {string} endWord
 * @param {string[]} wordList
 * @return {number}
 */
var ladderLengthBidirBFS = function(beginWord, endWord, wordList)
{
    if (!wordList.includes(endWord))
    {
        return 0;
    }

    const L = beginWord.length;

    let allComboMap = new Map();
    for (const word of wordList)
    {
        for (let i = 0; i < L; i++)
        {
            const newWord =
                word.substring(0, i) + "*" + word.substring(i + 1);

            if (!allComboMap.has(newWord))
            {
                allComboMap.set(newWord, [word]);
            }
            else
            {
                allComboMap.get(newWord).push(word);
            }
        }
    }

    let qBegin = [[beginWord, 1]];
    let qEnd = [[endWord, 1]];

    let visitedBegin = new Map();
    let visitedEnd = new Map();
    visitedBegin.set(beginWord, 1);
    visitedEnd.set(endWord, 1);

    const visitWordNode = (queue, visited, othersVisited) => {
        const currQueueLength = queue.length;

        for (let j = 0; j < currQueueLength; j++)
        {
            const [word, level] = queue.shift();

            for (let i = 0; i < L; i++)
            {
                const newWord =
                    word.substring(0, i) + "*" + word.substring(i + 1);
                
                if (!allComboMap.has(newWord))
                {
                    continue;
                }

                for (const adjacentWord of allComboMap.get(newWord))
                {
                    if (othersVisited.has(adjacentWord))
                    {
                        return level + othersVisited.get(adjacentWord);
                    }

                    if (!visited.has(adjacentWord))
                    {
                        visited.set(adjacentWord, level + 1);
                        queue.push([adjacentWord, level + 1]);
                    }
                }
            }
        }

        return -1;
    }

    let ans = -1;

    while (qBegin.length && qEnd.length)
    {
        if (qBegin.length <= qEnd.length)
        {
            ans = visitWordNode(qBegin, visitedBegin, visitedEnd);
        }
        else
        {
            ans = visitWordNode(qEnd, visitedEnd, visitedBegin);
        }

        if (ans > -1)
        {
            return ans;
        }
    }

    return 0;
};