/**
 * @param {number[][]} mat
 * @return {number[][]}
 */
var updateMatrix = function(mat)
{
    const valid = (row, col) => {
        return 0 <= row && row < m && 0 <= col && col < n && mat[row][col] == 1;
    }

    // Can create a copy of mat to avoid modifying the input
    const m = mat.length;
    const n = mat[0].length;

    let queue = [];
    let seen = [];
    for (let i = 0; i < m; i++)
    {
        seen.push(new Array(n).fill(false));
    }

    for (let row = 0; row < m; row++)
    {
        for (let col = 0; col < n; col++)
        {
            if (mat[row][col] == 0)
            {
                queue.push([row, col]);
                seen[row][col] = true;
            }
        }
    }

    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];
    let steps = 0;

    while (queue.length)
    {
        let currentLength = queue.length;
        let nextQueue = [];
        steps++;

        for (let i = 0; i < currentLength; i++)
        {
            const [row, col] = queue[i];
            for (const [dcol, drow] of directions)
            {
                const nextRow = row + drow;
                const nextCol = col + dcol;

                if (valid(nextRow, nextCol) && !seen[nextRow][nextCol])
                {
                    seen[nextRow][nextCol] = true;
                    nextQueue.push([nextRow, nextCol]);
                    mat[nextRow][nextCol] = steps;
                }
            }
        }

        queue = nextQueue;
    }

    return mat;
};