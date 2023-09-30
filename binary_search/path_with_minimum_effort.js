/**
 * @param {number[][]} heights
 * @returns {number}
 */
var minimumEffortPath = function(heights)
{
    const valid = (row, col) => {
        return 0 <= row && row < nrows && 0 <= col && col < ncols;
    }

    const check = effort => {
        const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];
        let seen = [];

        for (let i = 0; i < nrows; i++)
        {
            seen.push(new Array(ncols).fill(false));
        }
        seen[0][0] = true;

        let stack =[[0, 0]];

        while (stack.length)
        {
            const [row, col] = stack.pop();

            if (row == nrows - 1 && col == ncols - 1)
            {
                return true;
            }

            for (const [dcol, drow] of directions)
            {
                const nextRow = row + drow;
                const nextCol = col + dcol;

                if (valid(nextRow, nextCol) && !seen[nextRow][nextCol])
                {
                    if (Math.abs(heights[nextRow][nextCol] - heights[row][col])
                        <= effort)
                    {
                        seen[nextRow][nextCol] = true;
                        stack.push([nextRow, nextCol]);
                    }
                }
            }
        }

        return false;
    }

    let nrows = heights.length;
    let ncols = heights[0].length;

    let left = 0;
    let right = 0;
    for (const arr of heights)
    {
        right = Math.max(right, Math.max(...arr));
    }

    while (left <= right)
    {
        const mid = Math.floor((left + right) / 2);

        if (check(mid))
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;
}