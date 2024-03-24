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

/**
 * @param {number} m
 * @param {number} n
 * @returns {number}
 */
var uniquePathsDS2 = function(m, n)
{
    let dp = [];
    for (let row = 0; row < m; row++)
    {
        dp.push(new Array(n).fill(0));
    }
    dp[0][0] = 1;

    for (let row = 0; row < m; row++)
    {
        for (let col = 0; col < n; col++)
        {
            if (row > 0)
            {
                dp[row][col] += dp[row - 1][col];
            }

            if (col > 0)
            {
                dp[row][col] += dp[row][col - 1];
            }
        }
    }

    return dp[m - 1][n - 1];
};

/**
 * @param {number} m
 * @param {number} n
 * @returns {number}
 */
var uniquePathsDS3 = function(m, n)
{
    let dp = new Array(n).fill(0);
    dp[0] = 1;

    for (let row = 0; row < m; row++)
    {
        let next_row = new Array(n).fill(0);
        for (let col = 0; col < n; col++)
        {
            next_row[col] += dp[col];
            if (col > 0)
            {
                next_row[col] += next_row[col - 1];
            }
        }

        dp = next_row;
    }

    return dp[n - 1];
};
