var shortestPath = function(grid, k)
{
    const valid = (row, col) => {
        return 0 <= row && row < m && 0 <= col && col < n;
    }

    const m = grid.length;
    const n = grid[0].length;

    let queue = [[0, 0, k]];
    let seen = [];

    for (let i = 0; i < m; i++)
    {
        seen.push(new Array(n).fill(-1));
    }

    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];
    let steps = 0;

    while (queue.length)
    {
        let currentLength = queue.length;
        let nextQueue = [];

        for (let i = 0; i < currentLength; i++)
        {
            let [row, col, remain] = queue[i];
            if (row == m - 1 && col == n - 1)
            {
                return steps;
            }

            // If current square is an obstacle, need to spend a removal
            if (grid[row][col] == 1)
            {
                if (remain == 0)
                {
                    continue;
                }
                else
                {
                    remain--;
                }
            }

            // If square has already been visited with more removals then the
            // current path is pointless since more removals is better
            if (seen[row][col] >= remain)
            {
                continue;
            }

            seen[row][col] = remain;
            for (const [dcol, drow] of directions)
            {
                const nextRow = row + drow;
                const nextCol = col + dcol;

                if (valid(nextRow, nextCol))
                {
                    nextQueue.push([nextRow, nextCol, remain]);
                }
            }
        }

        queue = nextQueue;
        steps++;
    }

    return -1;
}