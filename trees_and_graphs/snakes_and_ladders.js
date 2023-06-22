/**
 * @param {number[][]} board
 * @return {number}
 */
var snakesAndLaddersBFS = function(board)
{
    const n = board.length;
    let cells = new Array(n * n + 1);

    let label = 1;
    let columns = [...Array(n).keys()];

    for (let row = n - 1; row >= 0; row--)
    {
        for (let column of columns)
        {
            cells[label++] = [row, column];
        }

        columns.reverse();
    }

    let dist = new Array(n * n + 1).fill(-1);
    dist[1] = 0;

    let queue = [1];
    while (queue.length)
    {
        const currLength = queue.length;
        let nextQueue = [];

        for (let ele = 0; ele < currLength; ele++)
        {
            const curr = queue[ele];

            for (let next = curr + 1; next <= Math.min(curr + 6, n * n); next++)
            {
                const [row, col] = cells[next];

                const destination =
                    board[row][col] != -1 ? board[row][col] : next;

                if (dist[destination] == -1)
                {
                    dist[destination] = dist[curr] + 1;
                    nextQueue.push(destination);
                }
            }
        }

        queue = nextQueue;
    }

    return dist[n * n];
};

// Dijkstra's algorithm solution will be skipped due to the lack of a built-in
// priority queue (requires external library or implementing one)