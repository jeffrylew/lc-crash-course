/**
 * @param {string} startGene
 * @param {string} endGene
 * @param {string[]} bank
 * @return {number}
 */
var minMutation = function(startGene, endGene, bank)
{
    let queue = [startGene];
    let seen = new Set([startGene]);

    let steps = 0;

    while (queue.length)
    {
        const nodesInQueue = queue.length;
        let nextQueue = [];

        for (let j = 0; j < nodesInQueue; j++)
        {
            const node = queue[j];

            if (node == endGene)
            {
                return steps;
            }

            for (const c of "ACGT")
            {
                for (let i = 0; i < node.length; i++)
                {
                    const neighbor =
                        node.substring(0, i) + c + node.substring(i + 1);

                    if (!seen.has(neighbor) && bank.includes(neighbor))
                    {
                        seen.add(neighbor);
                        nextQueue.push(neighbor);
                    }
                }
            }
        }

        queue = nextQueue;
        steps++;
    }

    return -1;
};