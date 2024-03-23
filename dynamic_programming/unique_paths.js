/**
 * @param {number} m
 * @param {number} n
 * @returns {number}
 */
var uniquePathsDS1 = function(m, n)
{
    const dp = (row, col) => {
        if (row + col == 0)
        {
            // Base case
            return 1;
        }

        if (memo[row][col] != -1)
        {
            return memo[row][col];
        }

        let num_ways = 0;
        if (row > 0)
        {
            num_ways += dp(row - 1, col);
        }

        if (col > 0)
        {
            num_ways += dp(row, col - 1);
        }

        memo[row][col] = num_ways;
        return num_ways;
    }

    let memo = [];
    for (let row = 0; row < m; row++)
    {
        memo.push(new Array(n).fill(-1));
    }

    return dp(m - 1, n - 1);
};
