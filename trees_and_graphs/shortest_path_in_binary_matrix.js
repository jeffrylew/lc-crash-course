/**
 * @param {number[][]} grid
 * @returns {number}
 */
var shortestPathBinaryMatrix = function(grid)
{
    const valid = (row, col) => {
        return 0 <= row
            && row < n
            && 0 <= col
            && col < n
            && grid[row][col] == 0;
    }

    if (grid[0][0] == 1)
    {
        return -1;
    }

    const n = grid.length;
    let seen = [];
    for (let i = 0; i < n; i++)
    {
        seen.push(new Array(n).fill(false));
    }
    seen[0][0] = true;

    let queue = [[0, 0]]; // row, col

    const directions = [
        [0, 1], [1, 0], [1, 1], [-1, -1], [-1, 1], [1, -1], [0, -1], [-1, 0]];
    
    let steps = 0;

    while (queue.length)
    {
        let currentLength = queue.length;
        let nextQueue = [];
        steps++;

        for (let i = 0; i < currentLength; i++)
        {
            const [row, col] = queue[i];
            if (row == n - 1 && col == n - 1)
            {
                return steps;
            }

            for (const [dx, dy] of directions)
            {
                const nextRow = row + dy;
                const nextCol = col + dx;

                if (valid(nextRow, nextCol) && !seen[nextRow][nextCol])
                {
                    seen[nextRow][nextCol] = true;
                    nextQueue.push([nextRow, nextCol]);
                }
            }
        }

        queue = nextQueue;
    }

    return -1;
};