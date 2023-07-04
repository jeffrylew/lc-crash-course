/**
 * @param {number[]} arr
 * @param {number} start
 * @return {boolean}
 */
var canReachBFS = function(arr, start)
{
    const n = arr.length;

    let queue = [start];

    while (queue.length)
    {
        const queueLength = queue.length;
        let nextQueue = [];

        for (let idx = 0; idx < queueLength; idx++)
        {
            const node = queue[idx];

            // Check if reached zero
            if (arr[node] == 0)
            {
                return true;
            }

            if (arr[node] < 0)
            {
                continue;
            }

            // Check available next steps
            if (node + arr[node] < n)
            {
                nextQueue.push(node + arr[node]);
            }

            if (node - arr[node] >= 0)
            {
                nextQueue.push(node - arr[node]);
            }

            // Mark as visited
            arr[node] = -arr[node];
        }

        queue = nextQueue;
    }

    return false;
};

/**
 * @param {number[]} arr
 * @param {number} start
 * @return {boolean}
 */
var canReachDFS = function(arr, start)
{
    if (start >= 0 && start < arr.length && arr[start] >= 0)
    {
        if (arr[start] == 0)
        {
            return true;
        }

        arr[start] = -arr[start];

        return canReachDFS(arr, start + arr[start])
            || canReachDFS(arr, start - arr[start]);
    }

    return false;
};