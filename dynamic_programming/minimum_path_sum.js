/**
 * @param {number[][]} grid
 * @returns {number}
 */
var minPathSumDS1 = function(grid) {
    const num_rows = grid.length;
    const num_cols = grid[0].length;

    let memo = [];
    for (let row = 0; row < num_rows; row++)
    {
        memo.push(new Array(num_cols).fill(-1));
    }

    const dp = (row, col) => {
        if (row + col == 0)
        {
            return grid[row][col];
        }

        if (memo[row][col] != -1)
        {
            return memo[row][col];
        }

        let min_sum = Number.MAX_SAFE_INTEGER;
        if (row > 0)
        {
            min_sum = Math.min(min_sum, dp(row - 1, col));
        }

        if (col > 0)
        {
            min_sum = Math.min(min_sum, dp(row, col - 1));
        }

        memo[row][col] = grid[row][col] + min_sum;
        return memo[row][col];
    };

    return dp(num_rows - 1, num_cols - 1);
};
