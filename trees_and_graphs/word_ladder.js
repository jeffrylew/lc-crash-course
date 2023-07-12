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