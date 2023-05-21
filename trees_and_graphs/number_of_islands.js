/**
 * @param {character[][]} grid
 * @returns {number}
 */
var numIslands = function(grid) {
    const valid = (row, col) => {
        return 0 <= row
            && row < m
            && 0 <= col
            && col < n
            && grid[row][col] == "1";
    }

    const dfsRecursive = (row, col) => {
        for (const [drow, dcol] of directions)
        {
            const nextRow = row + drow;
            const nextCol = col + dcol;

            if (valid(nextRow, nextCol) && !seen[nextRow][nextCol])
            {
                seen[nextRow][nextCol] = true;
                dfsRecursive(nextRow, nextCol);
            }
        }
    }

    const dfsIterative = (startRow, startCol) => {
        stack = [[startRow, startCol]]
        while (stack.length)
        {
            const [row, col] = stack.pop();
            for (const [drow, dcol] of directions)
            {
                const nextRow = row + drow;
                const nextCol = col + dcol;

                if (valid(nextRow, nextCol) && !seen[nextRow][nextCol])
                {
                    seen[nextRow][nextCol] = true;
                    stack.push([nextRow, nextCol]);
                }
            }
        }
    }

    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];
    const m = grid.length;
    const n = grid[0].length;
    let seen = [];

    for (let i = 0; i < m; i++)
    {
        seen.push(new Array(n).fill(false));
    }

    let ans = 0;
    for (let row = 0; row < m; row++)
    {
        for (let col = 0; col < n; col++)
        {
            if (grid[row][col] == "1" && !seen[row][col])
            {
                ans++;
                seen[row][col] = true;
                dfsRecursive(row, col);
                // dfsIterative(row, col);
            }
        }
    }

    return ans;
};